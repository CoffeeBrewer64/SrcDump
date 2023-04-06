a0 183

#include <types.h>
#include <iop.h>
#include <ios.h>
#include <iosc.h>
#include <ioslibc.h>
#include "debug.h"


#define WFS_RM_STACK_SIZE  0x2000
#define WFS_RM_PRIORITY    9
#define WFS_RM_NAME        "/dev/wfs"
#define WFS_REQUEST_Q_SIZE 256

/* IOCTL commands */
#define WFS_RM_IOCTL_SHA       0
#define WFS_RM_IOCTL_AES       1
#define WFS_RM_IOCTL_SHA_SYNC  2
#define WFS_RM_IOCTL_AES_SYNC  3
#define WFS_RM_IOCTL_HMAC      4
#define WFS_RM_IOCTL_HMAC_SYNC 5
#define WFS_RM_IOCTL_DIHASH    6

const u8 _initStack[WFS_RM_STACK_SIZE];
const u32 _initStackSize = sizeof(_initStack);
const u32 _initPriority = WFS_RM_PRIORITY;

static IOSMessage          wfsMsgQ[WFS_REQUEST_Q_SIZE];

#define BUFFER_SIZE     (64*1024)
#define ALIGNMENT_SIZE  64
static u8 buffer[BUFFER_SIZE+ALIGNMENT_SIZE];

static u32 __aesCnt    = 0;


static IOSError AESAsync(u8 sync)
{
    IOSError           rv;
    IOSMessageQueueId  MessageQueueId;
    IOSMessage         MassageQueue[1];
    IOSMessage         Message;
    IOSResourceRequest reply;
    IOSCSecretKeyHandle aesHandle;
    u8                  aesKey[16];
    u8                  ivData[16];

    int i;

    MessageQueueId = IOS_CreateMessageQueue( MassageQueue, 1 );
    if (MessageQueueId < 0) {
        printf("WFS-AES: Error: IOS_CreateMessageQueue failed : %d \n",
            MessageQueueId);
        return (MessageQueueId);
    }

    for (i=0;i<16;i++)
    {
        aesKey[i] = i; //dummy key
        ivData[i] = i;
    }
    IOSC_CreateObject(&aesHandle,  IOSC_SECRETKEY_TYPE, IOSC_ENC_SUBTYPE);
    IOSC_ImportSecretKey(aesHandle, 0, 0, IOSC_NOSIGN_NOENC, 0, 0, aesKey);

    u8* pInBuffer = (u8*)(((size_t)buffer+ALIGNMENT_SIZE-1)&~(ALIGNMENT_SIZE-1));

    __aesCnt++;

    u32 nCnt = 0;
    while (1)
    { 
        memset(pInBuffer,(u8)(nCnt+1),BUFFER_SIZE);

        if (sync) {  /* Using sync call */
            rv = IOSC_Encrypt(aesHandle, ivData, pInBuffer, BUFFER_SIZE, pInBuffer);
            if (rv != IOS_ERROR_OK) {
                printf("Error: IOSC_Encrypt() failed: i=%d rv=%d\n", nCnt, rv);
                break;
            }
        } else {  /* Using async call */
            rv = IOSC_EncryptAsync(aesHandle, ivData, pInBuffer, BUFFER_SIZE, pInBuffer, MessageQueueId, &reply);
            if (rv != IOS_ERROR_OK) {
                printf("Error: IOSC_EncryptAsync() failed: i=%d rv=%d\n", 
                       nCnt, rv);
                break;
            }
            rv = IOS_ReceiveMessage( MessageQueueId, &Message, IOS_MESSAGE_BLOCK );
            if (rv != IOS_ERROR_OK) {
                printf("Error: IOSC_ReceiveMessage() failed: i=%d rv=%d\n", 
                       nCnt, rv);
                break;
            }
        }  /* Using async */

        ++nCnt;
        if(nCnt==1000){
            if (sync)
                printf("WFS: AES (%08X): 1000 Done.\n", __aesCnt);
            else
                printf("WFS: AES Async (%08X): 1000 Done.\n", __aesCnt);
            break;
        }
    }

    IOSC_DeleteObject(aesHandle);
    IOS_DestroyMessageQueue(MessageQueueId);
    return rv;

}

extern char __version[];

int main(int argc, char **argv)
{

    IOSMessageQueueId wfsMsgQId;
	IOSMessage        inMsg;
          
    // prepare for message queue
    wfsMsgQId = IOS_CreateMessageQueue(wfsMsgQ, WFS_REQUEST_Q_SIZE);
    if (wfsMsgQId < 0) {
        printf("WFS: Error: IOS_CreateMessageQueue failed : %d \n",
            wfsMsgQId);
        return (wfsMsgQId);
    }

    IOS_RegisterResourceManager(WFS_RM_NAME, wfsMsgQId);

    printf("%s\n", __version);
    printf("*** WFS\n");

    wfsLog("*** WFS ***\n");

    // service messages
    while (IOS_ReceiveMessage(wfsMsgQId, &inMsg, IOS_MESSAGE_BLOCK
								) == IOS_ERROR_OK)
	{
		IOSResourceRequest *pReq = (IOSResourceRequest*)inMsg;
        IOSResourceIoctl *p_iri = (IOSResourceIoctl*)&pReq->args;

        switch (pReq->cmd)
        {
            case IOS_OPEN:{
                IOS_ResourceReply(pReq, IOS_ERROR_OK);
                break;
            }
            case IOS_CLOSE:{
                IOS_ResourceReply(pReq, IOS_ERROR_OK);
                break;
            }
            case IOS_IOCTL:{
                IOSError rv = IOS_ERROR_INVALID;
                switch (p_iri->cmd)
                {
                    case WFS_RM_IOCTL_AES: {
                        rv = AESAsync(0);
                        break;
                    }
                    default: {
                        printf("WFS: unknown IOCTL command %d\n", p_iri->cmd);
                        break;
                    }
                }
                IOS_ResourceReply(pReq, rv);
                break;
            }
            case IOS_REPLY:
            case IOS_READ:
            case IOS_WRITE:     
            case IOS_SEEK:               
            case IOS_IOCTLV:    
            default: 
                printf("unknown ios command %d\n", pReq->cmd);
                IOS_ResourceReply(pReq, IOS_ERROR_INVALID);
                break;
        }

	}
    
    return 0;

}

