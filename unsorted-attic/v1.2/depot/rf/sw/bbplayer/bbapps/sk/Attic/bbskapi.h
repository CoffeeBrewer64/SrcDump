#ifndef __BB_SK_API_HDR__
#define __BB_SK_API_HDR__


/*
 * To add an sk api function:
 *   1) add SK_API_CALL_ define
 *   2) add function prototype in this header
 *   3) implement function in skapi.c
 *   4) add the function to the array skapi_call_table (skapi.c)
 *   5) add entry stub to sysapp/libultra side skapi.s.
 */

/*
 * Function call mapping numbers, must be in order 0..end
 */

#define SK_API_CALL_GET_ID          0
#define SK_API_CALL_LAUNCH_BEGIN    1
#define SK_API_CALL_LAUNCH_DATA     2
#define SK_API_CALL_LAUNCH_END      3
#define SK_API_CALL_RECRYPT_BEGIN   4
#define SK_API_CALL_RECRYPT_DATA    5
#define SK_API_CALL_RECRYPT_STATE   6
#define SK_API_CALL_RECRYPT_END     7
#define SK_API_CALL_TEST1           8
#define SK_API_CALL_TEST2           9
#define SK_API_CALL_TEST3          10


/* sk api error and return codes. Negative implies failure. */
#define SK_API_SUCCESS                   0
#define SK_API_RECRYPT_NOT_REQUIRED      1
#define SK_API_RECRYPT_COMPLETE          2

#define SK_API_FAIL                     -1
#define SK_API_INVALID_TSRL             -2
#define SK_API_INVALID_CARL             -3
#define SK_API_INVALID_CPRL             -4
#define SK_API_INVALID_CRL              -5
#define SK_API_INVALID_CERT             -6
#define SK_API_INVALID_CONT_HASH        -7

/*
 * Function call declarations.
 *  NOTE: max number of args is 4, and they must fit into a0-a3.  
 */

#if defined(_LANGUAGE_C)

#include <PR/bbticket.h>
#include <PR/bbcert.h>
#include <PR/bbcrl.h>

typedef struct {
    BbCrlHead head;
    u8 *list; /* the actual list of revoked SNs */
    BbCertBase *certChain; /* cert chain, the actual layout is abutted
                            * Bb*Cert (i.e., BbRsaCert or BbEccCert)
                            * objects, in chain order, Root last. */
} BbCrlBundle;

typedef struct {
    BbTicket *ticket;
    BbCertBase *certChain;  /* cert chain, the actual layout is abutted
                            * Bb*Cert (i.e., BbRsaCert or BbEccCert)
                            * objects, in chain order, Root last. */
} BbTicketBundle;

typedef struct {
    BbCrlBundle *tsrl;  /* ticket server revocation list */
    BbCrlBundle *carl;  /* certificate authority revocation list */
    BbCrlBundle *cprl;  /* content publishing server revocation list */
    BbCrlBundle *crl;   /* content (CID) revocation list */
} BbAppLaunchCrls;
    

/*
 * The actual sk api function declarations. All functions
 * return SK_API_ return codes defined above. Any return
 * value < 0 is failure.
 */


/* get the bbid */
int skGetId(BbId *id);

/* begin app launching process. if success, proceed with skLaunchData()
 * calls.
 */
int skLaunchBegin(BbTicketBundle *ticket,
                  BbAppLaunchCrls *crls,
                  void *pKeyList);

/* call with app data till all data is fed to sk */
int skLaunchData(u8 *data, u32 size);

/* end app launch and determine success or failure */
int skLaunchEnd();

/* like skLaunchBegin, but will not launch app. primes sk for
 * ensuing skRecrypt*() calls.
 */
int skRecryptBegin(BbTicketBundle *ticket,
                   BbAppLaunchCrls *crls,
                   void *pKeyList);

/* input data chunk by chunk */
int skRecryptData(u8 *data, u32 size);

/* when recovering from aborted recryption attempt, this call must
 * be used to feed the already recrypted data before calling
 * skRecryptData to finish.
 */
int skRecryptComputeState(u8 *data, u32 size);

/* end recyrption and determine success */
int skRecryptEnd();

/* simple tests */
int skTest1(int a,int b);
int skTest2(int a,int b);
int skTest3(int a,int b);

#endif /* _LANGUAGE_C */

#endif


