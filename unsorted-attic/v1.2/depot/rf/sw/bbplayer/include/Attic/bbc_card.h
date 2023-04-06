#ifndef _BBC_CARD_H_
#define _BBC_CARD_H_
/*
 * Open Issues
 *	None
 */

#define BBC_OK 0	/* Successful return value */
#define BBC_BADCARD -1	/* Card has errors and requires reformat */
#define BBC_NOID -2	/* BBID is not present on Card */
#define BBC_NOSPACE -3	/* No space left on Card */
#define BBC_NOCARD -4	/* Card has been removed */
#define BBC_CARDCHANGE -5	/* Init() has not been called */
#define BBC_TOOMANY -6	/* Too many active handles */
#define BBC_BADHANDLE -7	/* Invalid handle */
#define BBC_ERROR -10	/* Generic error */

/*
 * Typically all functions return one of the above
 * error codes in case of errors. Success is indicated by
 * a return value of zero or a positive integer in case of
 * writes which indicates the number of bytes written.
 */

/*
 * BBCInit() must be called before any operations can
 * be performed on a card. If Init has not been called on
 * the card that is currently inserted, then BBC_CARDCHANGE
 * is returned.
 * 
 * Success is indicated by a return of zero, which indicates
 * that the card is good and all necessary files are present.
 * Depot may proceed with normal operations. In case of
 * error, Depot has to proceed with recovery steps.
 * Recovery consists of reformatting the entire
 * flash card. If this is called with BBC_NOWAIT, then
 * it returns immediately, else it will wait till a
 * Card has been inserted.
 *
 * Once all operations on the card have been completed,
 * call BBCClose();
 */
#define BBC_NDELAY	0x0001	/* non blocking call */
#define BBC_SYNC	0x0002	/* synchronous call */

typedef int BBCHandle;

/*
 * device is the USB reader device, e.g, /proc/bus/usb/001/002
 */
extern BBCHandle BBCInit(const char *device, int callType);
extern int BBCClose(BBCHandle h);


/*
 * cardSize is in kbytes
 * freeSpace is in kbytes and indicates the max content size
 *	that may be copied into the card
 * In case of error, Depot will initiate recovery procedures
 */
extern int BBCStats(BBCHandle h, int *cardSize, int *freeSpace);


/*
 * Returns the identity of the BB Card. May be called even if the
 * Init() or Stats() fails, in which case this will be recovered from any
 * backup copies etc. Returns the number of bytes written into
 * the buffer. BBC_NOID is returned if the 
 * the bbID cannot be recovered. The first 4 bytes of the buf
 * if present, will contain the bbHwRev. The remaining bytes
 * are for the BB Certificate, if present.
				  */
extern int BBCGetIdentity(BBCHandle h, int *bbID, void* buf, int len);
extern int BBCStoreIdentity(BBCHandle h, int bbID, const void* buf, int len);


/*
 * Formats the card, including bad block mapping etc.
 * Upon success, the Depot may proceed with copying all
 * of the necessary files on to the Card, which include
 * id.sys, crl.sys, ticket.sys, system area, cert.sys
 * These files may be of size zero if there is no data.
 * The sequence that will be followed is
 *	BBCFormatCard();
 *	BBCStoreIdentity();
 *	BBCVerifySKSA();
 *	BBCStoreCrls();
 *	BBCStoreCert();
 *	BBCStoreTickets();
 *	BBCStorePrivateData();
 *	BBCClose();
 */
extern int BBCFormatCard(BBCHandle h);


/*
 * BB Depot private data is stored in this file. Initially
 * we're expecting to store just the timestamp of last update.
 */
extern int BBCPrivateDataSize(BBCHandle h);
extern int BBCGetPrivateData(BBCHandle h, void* buf, int len);
extern int BBCStorePrivateData(BBCHandle h, const void* buf, int len);

/*
 * BB Depot user registration data
 */
extern int BBCUserDataSize(BBCHandle h);
extern int BBCGetUserData(BBCHandle h, void* buf, int len);
extern int BBCStoreUserData(BBCHandle h, const void* buf, int len);

/*
 * eTicket operations to get size of the "file", read eTickets
 * and update them. len is the size in bytes.
 */
extern int BBCTicketsSize(BBCHandle h);
extern int BBCGetTickets(BBCHandle h, void* buf, int len);
extern int BBCStoreTickets(BBCHandle h, const void* buf, int len);

/*
 * crl operations to get size of the "file", read crl
 * and update them. len is the size in bytes.
 */
extern int BBCCrlsSize(BBCHandle h);
extern int BBCGetCrls(BBCHandle h, void* buf, int len);
extern int BBCStoreCrls(BBCHandle h, const void* buf, int len);

/*
 * Certificate operations to get size of the "file", read certs
 * and update them. len is the size in bytes.
 */
extern int BBCCertSize(BBCHandle h);
extern int BBCGetCert(BBCHandle h, void* buf, int len);
extern int BBCStoreCert(BBCHandle h, const void* buf, int len);

/*
 * BBCContentListSize returns the number of content in the BB Card.
 * Size is in bytes.
 * BBCStoreContent invokes the callback function after finish
 * writing every 1Mbytes.  The argument is the total size of written data.
 * BBCRemoveContent does not remove signed game data.
 */
typedef unsigned int ContentId;
extern int BBCContentListSize(BBCHandle h);
extern int BBCGetContentList(BBCHandle h, ContentId list[], int size[], int nentries);
extern int BBCStoreContent(BBCHandle h, ContentId id, const void* buf, int size, void (*func)(int));
extern int BBCRemoveContent(BBCHandle h, ContentId id);

/*
 * Update the SK and SA on the Card if it does not match the
 * content that is passed in. Len is in bytes. Returns 0 if
 * contents were not updated, else returns the number of bytes
 * written. The actual layout is SK + SA license + SA. 
 * SK is fixed in size at 64KB
 * SA License is fixed in size at 16KB
 */
extern int BBCVerifySKSA(BBCHandle h, const void* buf, int len);

#endif /* _BBC_CARD_H_ */
