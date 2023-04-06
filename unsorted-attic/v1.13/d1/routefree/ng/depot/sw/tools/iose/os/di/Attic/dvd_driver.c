d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.12 2006/01/20 20:12:41 craig Exp $"
a74 2
bool            withinDummyCoverTime(void);

d143 1
a143 1
        if (resetTimeValid && withinDummyCoverTime() == false) {
d205 1
a205 1
            if (withinDummyCoverTime() == false) {
d387 10
d475 1
d477 5
a481 1
extern uint32_t IOS_GetTimer();
d484 1
a484 1
withinDummyCoverTime(void)
d486 1
a486 1
    uint32_t    currentTime, dummyEndTime;
d492 1
a492 1
    dummyEndTime = lastResetTime + DUMMY_COVER_INTR_TIME;
d494 2
a495 2
    if (dummyEndTime > lastResetTime) {
        if (currentTime < dummyEndTime && currentTime >= lastResetTime) {
d505 1
a505 1
         * the dummyEndTime wraps around past 0
d507 1
a507 1
        if (currentTime < dummyEndTime || currentTime >= lastResetTime) {
d514 1
a514 1
}
a517 42
#ifdef obsolete
#define DI_OTHER_MESG_POOL_SIZE         5

static struct diOtherMesg otherMesgPool[DI_OTHER_MESG_POOL_SIZE];

diOtherMesg_t *
newDiOtherMesg()
{
    for (int i = 0; i < DI_OTHER_MESG_POOL_SIZE; i++) {
        if (otherMesgPool[i].inUse == false) {
            otherMesgPool[i].inUse = true;
            return(otherMesgPool + i);
        }
    }
    diFatalError("Unable to allocate a diOtherMesg");
    /* Code shouldn't reach here */
    return(NULL);
}

/* ---------------------------------------------------------------------- */

void
freeDiOtherMesg(diOtherMesg_t *mesg)
{
    if (mesg->inUse == true) {
        mesg->inUse = false;
    }
    if (mesg->inUse == false) {
        printf ("Warning: freeing a free diOtherMesg!\n");
    }
}

/* ---------------------------------------------------------------------- */

static void
initDiMesgPool(void)
{
    for (int i = 0; i < DI_OTHER_MESG_POOL_SIZE; i++) {
        otherMesgPool[i].inUse = false;
    }
}
#endif // obsolete
