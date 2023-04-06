#define STACKSIZE	0x2000

/* monitor requests */
#define REQ_PING		1
#define REQ_POWER_OFF		2
#define REQ_WRITE_MEM		3
#define REQ_READ_MEM		4
#define REQ_JUMP		5
#define REQ_WRITE_BLOCK		6
#define REQ_READ_BLOCK		7
#define REQ_READ_DIR		8
#define REQ_WRITE_FILE		9
#define REQ_READ_FILE		10
#define REQ_DELETE_FILE		11
#define REQ_EXEC_FILE		12
#define REQ_SCAN_BLOCKS		13
#define REQ_DBG_TEST		14
#define REQ_RENAME_FILE		15
#define REQ_WRITE_BLOCK_SP	16
#define REQ_READ_BLOCK_SP	17
#define REQ_FS_INIT		18
#define REQ_SUM_FILE		19
#define REQ_FREE_BLKS		20
#define REQ_CARD_SIZE		21
