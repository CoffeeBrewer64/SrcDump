a0 616

#include <types.h>
#include <iop.h>
#include <ios.h>
#include <iosc.h>
#include <ioslibc.h>
#include <fs.h>
#include <estypes.h>
#include <es.h>


static char const __version[] = "$IOSVersion: WFS-X : "BUILD_TIME" "MEM2_SIZE" $";

#define WFS_RM_STACK_SIZE  0x2000
#define WFS_RM_PRIORITY    9
#define WFS_RM_NAME        "/dev/wfs"
#define WFS_REQUEST_Q_SIZE 256

/* IOCTL commands */
#define WFS_RM_IOCTL_AES       1

const u8 _initStack[WFS_RM_STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = WFS_RM_PRIORITY;

static IOSMessage          _wfsMsgQ[WFS_REQUEST_Q_SIZE];

/* Static buffer */
#define BUFFER_SIZE         (64*1024)
#define ALIGNMENT_SIZE      64
static u8 _buffer1[BUFFER_SIZE+ALIGNMENT_SIZE] __attribute__ ((aligned(64)));
static u8 _buffer2[BUFFER_SIZE+ALIGNMENT_SIZE] __attribute__ ((aligned(64)));

#define LARGE_BUFFER_SIZE   ((6*64*1024)+(40*1024))
static u8 _buffer3[LARGE_BUFFER_SIZE] __attribute__ ((aligned(64)));


/* Data buffer from shared heap */
#define MAIN_DATA_BUF_SIZE  1024
static u8 *_shDataBuf = NULL;

#define KEY_DATA_BUF_SIZE   32
#define RAND_DATA_BUF_SIZE  64

static u8 _randBuffer[RAND_DATA_BUF_SIZE] __attribute__ ((aligned(64)));
static u8 _keyBuffer[20] __attribute__ ((aligned(64)));

static IOSCSecretKeyHandle  _keyHandle;
static u8 _keyHandleValid = 0;  /* Flag to indicate if key handle is valid */

/* Test directory and file name */
#define TEST_DIRNAME        "/wfs/testdir"
#define TEST_FILENAME       "/wfs/testdir/test1.log"

#define TEST_DIRNAME_ALT    "/shared2/wfs/testdir"
#define TEST_FILENAME_ALT   "/shared2/wfs/testdir/test1.log"

/* Periodic timer settings */
#define TMR_MSG             0xbeefbeef
//#define TMR_INTERVAL        500000
#define TMR_INTERVAL        700000

/* Process Id, Uid, and Gid of running RM */
static IOSProcessId     _mainPid;
static IOSUid           _mainUid;
static IOSGid           _mainGid;

/* Device Id of system */
static ESId             _devId = 0;

/* Need to allocate buffers from shared heap to communicate with
ISFS and ES due to memory protection scheme */
static u8 *_shFsBuf = NULL;
static u8 *_shEsBuf = NULL;
extern void *__isfsBuf;
extern void *__esBuf;

/* Flag to indicate if running thread is using correct WFS process Id */
static u8 _realWfsPid = 0;

/* Flag to indicate if interface libraries (ES, FS) have been initialized */
static u8 _libsInitialized = 0;

/* Flags to indicate if test directory has been initialized or removed */
static u8 _testDirInitialized = 0;
static u8 _testDirRemoved = 0;

extern ESError TestWfsStream(void);


/*
 * This funtion allocates shared buffers to initialize both ISFS and ES
 * libraries.
 */
static IOSError InitSharedBuffers()
{

    ESError rv = ES_InitLib();
    if (rv != ES_ERR_OK) {
        printf("WFS-X: Failed to initialize ES library, rv=%d\n", rv);
        return rv;
    }

    // Overload ISFS internal buffer in library
    _shFsBuf = IOS_Alloc(0, ISFS_INITLIB_BUFSIZE);
    if (_shFsBuf == NULL) {
        printf("WFS-X: Failed to allocate ISFS buffer %d\n", 
                ISFS_INITLIB_BUFSIZE);
        return IOS_ERROR_MAX;
    }
    __isfsBuf = _shFsBuf;
    printf("WFS-X: Allocated memory for ISFS buffer\n");

    // Overload ES internal buffer in library
    _shEsBuf = IOS_Alloc(0, ES_BUF_SIZE);
    if (_shEsBuf == NULL) {
        printf("WFS-X: Failed to allocate ES buffer %d\n", ES_BUF_SIZE);
        return IOS_ERROR_MAX;
    }
    __esBuf = _shEsBuf;
    printf("WFS-X: Allocated memory for ES buffer\n");

    // Allocate shared buffer
    _shDataBuf = IOS_Alloc(0, MAIN_DATA_BUF_SIZE);
    if (_shDataBuf == NULL) {
        printf("WFS-X: Failed to allocate memory %d for data buffer\n", 
               MAIN_DATA_BUF_SIZE);
        return IOS_ERROR_MAX;
    }
    printf("WFS-X: Allocated memory for data buffers\n");

    // Initialize large test buffer
    memset(_buffer3, 0x53, LARGE_BUFFER_SIZE);
    _buffer3[LARGE_BUFFER_SIZE-4] = 0xde;
    _buffer3[LARGE_BUFFER_SIZE-3] = 0xad;
    _buffer3[LARGE_BUFFER_SIZE-2] = 0xbe;
    _buffer3[LARGE_BUFFER_SIZE-1] = 0xef;

    _libsInitialized = 1;

    return IOS_ERROR_OK;
}


/* 
 * This routine simply frees all the allocated buffers from the shared heap.
 */
static void FreeSharedBuffers()
{
    if (_shFsBuf) 
        IOS_Free(0, _shFsBuf);
    if (_shEsBuf) 
        IOS_Free(0, _shEsBuf);
    if (_shDataBuf) 
        IOS_Free(0, _shDataBuf);
}


/* 
 * This routine creates the test directory and test file under "/wfs".
 * It will fail if the running thread does not have correct WFS process id.
 */
static IOSError InitWfsTestDirectory(u8 *dirName, u8 *fileName)
{
    ISFSError    rc = ISFS_ERROR_OK;
    u32          num, attr, ownerAcc, groupAcc, othersAcc;
    IOSUid       uid;
    IOSGid       gid;


    /* Create wfs test directory if does not exist*/
    rc = ISFS_ReadDir(dirName, NULL, &num);
    if (rc == ISFS_ERROR_NOEXISTS) {
        rc = ISFS_CreateDir(dirName, 0, ISFS_RW_ACCESS, 0, 0);
        if (rc != ISFS_ERROR_OK) {
            if (_realWfsPid)
                printf("WFS-X: Failed to create directory (%s), rc=%d\n",
                    dirName, rc);
            else
                printf("WFS-X: Failed to create directory (%s), rc=%d "
                    "-> OK (expected)\n", dirName, rc);
            goto out;
        }
    }
    printf("WFS-X: Created directory (%s)\n", dirName);

    /* Create the test file with only onwer read-write access */
    rc = ISFS_CreateFile((const u8 *)fileName, 0,
                         ISFS_RW_ACCESS, 0, 0);
    if ((rc != ISFS_ERROR_OK) && (rc != ISFS_ERROR_EXISTS)) {
        printf("WFS-X: Failed to create file (%s), rc=%d\n", fileName, rc);
        goto out;
    }
    printf("WFS-X: Created file (%s)\n", fileName);

    rc = ISFS_GetAttr(fileName, &uid, &gid, &attr, &ownerAcc, &groupAcc,
                &othersAcc);
    if (rc != ISFS_ERROR_OK) {
        printf("WFS-X: Failed to get attributes for file (%s), rc=%d\n",
            fileName, rc);
        goto out;
    }
    printf("WFS-X: File: UID:0x%x, GID:0x%x, attr:0x%x, own:0x%x, grp:0x%x, "
           "other:0x%x\n", uid, gid, attr, ownerAcc, groupAcc, othersAcc);

    if ((uid!=_mainUid) && (gid!=_mainGid) && (ownerAcc!=ISFS_RW_ACCESS) &&
        (groupAcc!=0) && (othersAcc!=0)) {
        printf("WFS-X: Incorrect attributes for file (%s), rc=%d\n",
            fileName, rc);
        goto out;
    }

    _testDirInitialized = 1;

out:
    return(rc);

}


/* 
 * This routine removes the test directory and file under "/wfs"
 */
static IOSError CleanupWfsTestDirectory(u8 *dirName, u8 *fileName)
{
    ISFSError    rc = ISFS_ERROR_OK;

    if ((!_testDirInitialized) || (_testDirRemoved)) {
        return(rc);
    }

    printf("WFS-X: Cleaning up WFS test directory\n");
    rc = ISFS_Delete(fileName);
    if (rc != ISFS_ERROR_OK) {
        printf("WFS-X: Failed to delete file (%s), rc=%d\n",
            fileName, rc);
    }

    rc = ISFS_Delete(dirName);
    if (rc != ISFS_ERROR_OK) {
        printf("WFS-X: Failed to delete directory (%s), rc=%d\n",
            dirName, rc);
    }

    _testDirRemoved = 1;

    return(rc);

}


/* 
 * This routine creates a random key using device id
 */
static IOSError GenerateSecretKey(u8 *inBuf, u8 *keyBuf)
{
    IOSError        rv = IOS_ERROR_OK;
    IOSCHashContext hashContext;

    *(u32 *)inBuf = _devId;
    rv = IOSC_GenerateHash(hashContext, 0, 0, IOSC_HASH_FIRST, 0);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to generate hash (first), rv=%d\n", rv);
        goto out;
    }
    rv = IOSC_GenerateHash(hashContext, inBuf, RAND_DATA_BUF_SIZE, 
             IOSC_HASH_LAST, keyBuf);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to generate hash (last), rv=%d\n", rv);
        goto out;
    }

out:
    return rv;
}


/* 
 * This routine imports the secret key to IOSC
 */
static IOSError ImportSecretKey(IOSCSecretKeyHandle *keyHandle, u8 *keyBuf)
{
    IOSError rv = IOS_ERROR_OK;

    rv = IOSC_CreateObject(keyHandle, IOSC_SECRETKEY_TYPE, IOSC_ENC_SUBTYPE);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to create key object, rv=%d\n", rv);
        goto out;
    }

    rv = IOSC_ImportSecretKey(*keyHandle, 0,0, IOSC_NOSIGN_NOENC, 0,0, keyBuf);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to import secret key, rv=%d\n", rv);
        goto out;
    }

out:
    return rv;
}


/* 
 * This routine saves the secret key to test file
 */
static IOSError GenerateAndSaveRandToFile(u8 *fileName, u8 *dataBuf)
{
    IOSError rv = IOS_ERROR_OK;
    IOSFd    fd = -1;

    if (!_testDirInitialized) {
        printf("WFS-X: Test directory is not initialized!\n");
        rv = IOS_ERROR_INVALID;
        goto out;
    }

    fd = ISFS_Open(fileName, ISFS_WRITE_ACCESS);
    if (fd < 0) {
        printf("WFS-X: Failed to open file (%s), rv=%d\n", fileName, fd);
        goto out;
    }
    printf("WFS-X: Opened file (%s)\n", fileName);

    rv = IOSC_GenerateRand(dataBuf, RAND_DATA_BUF_SIZE);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to generate random, rv=%d\n", rv);
        goto out;
    }
    printf("WFS-X: Generated random number\n");

    rv = ISFS_Write(fd, dataBuf, RAND_DATA_BUF_SIZE);
    if (rv != RAND_DATA_BUF_SIZE) {
        printf("WFS-X: Failed to write %d bytes, rv=%d\n", RAND_DATA_BUF_SIZE,
            rv);
        if ((_realWfsPid) && (rv == IOS_ERROR_ACCESS)) {
            printf("WFS-X: Retrying writing to file (%s) using shared buffer\n",
                fileName);
            memcpy(_shDataBuf, dataBuf, RAND_DATA_BUF_SIZE);
            rv = ISFS_Write(fd, _shDataBuf, RAND_DATA_BUF_SIZE);
            if (rv != RAND_DATA_BUF_SIZE) {
                printf("WFS-X: Failed to write %d bytes (again), rv=%d\n",
                    RAND_DATA_BUF_SIZE, rv);
                goto out;
            }
        }
        else
            goto out;
    }
    printf("WFS-X: Wrote %d bytes to file (%s)\n", RAND_DATA_BUF_SIZE,
        fileName);
    
    rv = ISFS_Close(fd);
    if (rv != ISFS_ERROR_OK) {
        printf("WFS-X: Failed to close file (%d), rv=%d\n", fd, rv);
        goto out;
    }
    fd = -1;
    
out:
    if (fd >= 0)
        ISFS_Close(fd);
    return rv;

}


/* 
 * This routine encrypts test data using the imported key handle
 */
static IOSError EncryptData(IOSCSecretKeyHandle keyHandle, u8 *inBuf, u8 *outBuf)
{
    IOSError  rv = IOS_ERROR_OK;
    u8        ivData[16];
    u32       i;

    for (i=0; i<16; i++) {
        ivData[i] = i;
    }

    rv = IOSC_Encrypt(keyHandle, ivData, inBuf, BUFFER_SIZE, outBuf);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: IOSC_Encrypt failed, rv=%d\n", rv);
    }

    return rv;
}


/* 
 * This routine performs test encryption by using IOSC_Encrypt() API.
 */
static IOSError TestEncrypt()
{
    IOSError           rv = IOS_ERROR_OK;
    IOSCSecretKeyHandle aesHandle;
    u8                  aesKey[16];
    u8                  ivData[16];
    u8*                 pInBuffer;

    int i;

    for (i=0;i<16;i++) {
        aesKey[i] = i;      //dummy key
        ivData[i] = i;
    }

    IOSC_CreateObject(&aesHandle,  IOSC_SECRETKEY_TYPE, IOSC_ENC_SUBTYPE);
    IOSC_ImportSecretKey(aesHandle, 0, 0, IOSC_NOSIGN_NOENC, 0, 0, aesKey);

    pInBuffer = (u8*)(((size_t)_buffer1+ALIGNMENT_SIZE-1)&~(ALIGNMENT_SIZE-1));
    memset(pInBuffer, 0xab, BUFFER_SIZE);

    rv = IOSC_Encrypt(aesHandle, ivData, pInBuffer, BUFFER_SIZE, pInBuffer);
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Error: IOSC_Encrypt() failed, rv=%d\n", rv);
    }

    IOSC_DeleteObject(aesHandle);

    return rv;
}


/*
 * Main
 */
int main(int argc, char **argv)
{

    IOSError           rv = IOS_ERROR_OK;
    IOSMessageQueueId  msgQId;
	IOSMessage         inMsg;
    IOSTimerId         timer1 = -1;
	IOSResourceRequest *pReq;
    IOSResourceIoctl   *p_iri;

    u32                cnt = 0;
          
    // prepare for message queue
    msgQId = IOS_CreateMessageQueue(_wfsMsgQ, WFS_REQUEST_Q_SIZE);
    if (msgQId < 0) {
        printf("WFS-X: Error: IOS_CreateMessageQueue failed: %d \n",
            msgQId);
        return (msgQId);
    }

    IOS_RegisterResourceManager(WFS_RM_NAME, msgQId);

    printf("%s\n", __version);

    /* Retrieve pid, uid, and gid of running thread */
    _mainPid = IOS_GetProcessId();
    _mainUid = IOS_GetUid();
    _mainGid = IOS_GetGid();

    printf("\nWFS-X: PID=0x%x UID=0x%x GID=0x%x\n",_mainPid,_mainUid,_mainGid);
    if (_mainPid == IOS_WFS_PROCESS) {
        _realWfsPid = 1;
        printf("WFS-X: Running with correct WFS Process Id (%d)\n",
            _mainPid);
    } else {
        printf("WFS-X: Running with *** WRONG *** WFS Process Id (%d)\n",
            _mainPid);
    }

    /* Initialize shared buffers for ES & ISFS libraries */
    rv = InitSharedBuffers();
    if (rv != IOS_ERROR_OK) {
        printf("WFS-X: Failed to initialize shared buffers -> QUIT\n");
        goto main_out;
    }

    /* Create test directory and file under "/wfs" */
    rv = InitWfsTestDirectory(TEST_DIRNAME, TEST_FILENAME);
    if (rv != IOS_ERROR_OK) {
        if (_realWfsPid) {
            printf("WFS-X: Failed to initialize WFS test directory -> QUIT\n");
            goto main_out;
        } else {
            printf("WFS-X: Failed to initialize WFS test directory -> OK "
               "(expected)\n");
        }
    }

    /* Retrieve system device id */
    rv = ES_GetDeviceId(&_devId);
    if (rv != ES_ERR_OK) {
        printf("WFS-X: Failed to get device Id, rv=%d -> QUIT\n", rv);
        goto main_out;
    }
    printf("WFS-X: Device Id = 0x%x\n", _devId);

    /* Create periodic timer */
    timer1 = IOS_CreateTimer(0, TMR_INTERVAL, msgQId, TMR_MSG);
    if (timer1 < 0) {
        printf("WFS-X: Failed to create timer, rv=%d -> QUIT\n", timer1);
        goto main_out;
    }

    // Service messages
    cnt = rv = 0;
    while (IOS_ReceiveMessage(msgQId, &inMsg, IOS_MESSAGE_BLOCK
                             ) == IOS_ERROR_OK) {

        if (inMsg == TMR_MSG) {
            cnt++;
            printf("WFS-X: Got timer message #%d\n", cnt);
            switch (cnt) {
                case 1:
                    rv = GenerateAndSaveRandToFile(TEST_FILENAME, _randBuffer);
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Generated and saved random value\n");
                    } else {
                        if (_realWfsPid) {
                            printf("WFS-X: Failed to generate and save random "
                                "value, rv=%d\n", rv);
                        }
                        else {
                            printf("WFS-X: Failed to generate and save random "
                                "value, rv=%d -> OK (expected)\n", rv);
                        }
                    }
                    break;
                case 2:
                    rv = GenerateSecretKey(_randBuffer, _keyBuffer);
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Generated secret key\n");
                    } else {
                        printf("WFS-X: Failed to generate secret key, rv=%d\n",
                            rv);
                    }
                    break;
                case 3:
                    rv = ImportSecretKey(&_keyHandle, _keyBuffer);
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Imported secret key\n");
                        _keyHandleValid = 1;
                    } else {
                        printf("WFS-X: Failed to import secret key, rv=%d\n",
                            rv);
                    }
                    break;
                case 4:
                    rv = EncryptData(_keyHandle, _buffer1, _buffer2);
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Encrypted data\n");
                    } else {
                        printf("WFS-X: Failed to encrypt data, rv=%d\n",
                            rv);
                    }
                   break;
                case 5:
                    rv = TestEncrypt();
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Test encryption\n");
                    } else {
                        printf("WFS-X: Failed to run encryption test, rv=%d\n",
                            rv);
                    }
                    break;
                case 6:
                    rv = TestWfsStream();
                    if (rv == IOS_ERROR_OK) {
                        printf("WFS-X: Test WFS stream\n");
                    } else {
                        printf("WFS-X: Failed to run WFS stream test, rv=%d\n",
                            rv);
                    }
                    break;
                default: 
                    IOS_DestroyTimer(timer1);
                    CleanupWfsTestDirectory(TEST_DIRNAME, TEST_FILENAME);
                    printf("\nWFS-X: Waiting for request...\n");
                    break;
            }
            continue;
        }

		pReq = (IOSResourceRequest*)inMsg;
        p_iri = (IOSResourceIoctl*)&pReq->args;

        switch (pReq->cmd) {
            case IOS_OPEN:
            case IOS_CLOSE:
                IOS_ResourceReply(pReq, IOS_ERROR_OK);
                break;
            case IOS_IOCTL:{
                IOSError rv = IOS_ERROR_INVALID;
                switch (p_iri->cmd)
                {
                    case WFS_RM_IOCTL_AES: {
                        rv = TestEncrypt();
                        break;
                    }
                    default: {
                        printf("WFS-X: unknown IOCTL command %d\n", p_iri->cmd);
                        break;
                    }
                }
                IOS_ResourceReply(pReq, rv);
                break;
            }
            default: 
                printf("WFS-X: Error: unknown command %d\n", pReq->cmd);
                IOS_ResourceReply(pReq, IOS_ERROR_INVALID);
                break;
        }

	}
    
main_out:
    if (_keyHandleValid) IOSC_DeleteObject(_keyHandle);
    FreeSharedBuffers();
    return (rv);

}

