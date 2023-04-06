/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

#include <iostypes.h>
#include <ios.h>
#include <ioslibc.h>
#include <iosiobuf.h>

/* Returns pointer to Queue with specified chain removed */
IOSIobuf *
IOS_DequeueIob(IOSIobuf *iobQueue, IOSIobuf *iobChain)
{
  IOSIobuf *iob = iobQueue;
  if ( NULL == iobQueue || NULL == iobChain ) {
      printf("Dequeueing chain %p from queue %p failed\n", iobChain, iobQueue);
      return NULL;
  }
  if ( iobChain == iobQueue ) {  /* First element */
      iob = iobQueue->link;
      goto done;
  }
  while ( NULL != iob ) {
      if ( iobChain == iob->link ) {
           iob->link = iobChain->link; /* remove chain */
           iob = iobQueue;  /* return queue */
           goto done; 
      }
      iob = iob->link;
  }
  /* Did not find chain. Just return original queue */
  iob = iobQueue;
done:
  return iob;
}

IOSError 
IOS_FreeIobChain(IOSIobuf *chain)
{
    IOSError ret = IOS_ERROR_OK;
    IOSIobuf *tmp, *next;
    if ( NULL == chain )
        return IOS_ERROR_INVALID;

    tmp = chain;
    next = chain->next;
    while ( NULL != tmp) {
        if ( IOS_ERROR_OK != (ret = IOS_FreeIob(tmp))) {
            printf("IOS_FreeIob(%p) failed\n", tmp);
            goto done;
        }
//        printf("Freed: %p\n", tmp);
        tmp = next;
        if ( tmp != NULL )
            next = tmp->next;
    }
done:
    return ret;
}

IOSIobuf *
IOS_BreakIobChain(IOSIobuf *chain, IOSIobuf *iob)
{
    IOSIobuf *tmp;
    if ( iob == chain ) {  /* First element */
        tmp = iob->next;
        iob->next = NULL;
        return tmp;
    }
    tmp = chain;
    while ( NULL != tmp) {
        if ( tmp->next == iob ) {
            tmp->next = NULL; 
            goto done; 
      }
      tmp = tmp->next;
  }
  printf("iobuf %p not found in chain %p", iob, chain);
done:
   return iob;
}

IOSIobuf *
IOS_EnchainIob(IOSIobuf *chain, IOSIobuf *iob)
{
  IOSIobuf *tmp = chain;
  if ( NULL == chain || (iob == chain) )
      return chain;

  while ( tmp->next != NULL ) /* find tail */
      tmp = tmp->next;
  tmp->next = iob;
  return chain;
}

IOSIobuf *
IOS_PrependIob(IOSIobuf *chain, IOSIobuf *iob)
{
    if ( NULL == iob || (chain == iob) )
        return chain;
    iob->next = chain;
    return iob;
}

IOSIobuf *
IOS_EnqueueIob(IOSIobuf *queue, IOSIobuf *chain)
{
  IOSIobuf *tmp = queue;
  if ( NULL == queue || (queue == chain) ) {
      printf("Enqueuing %p to queue %p failed\n", chain, queue);
      goto done;
  }
  while ( tmp->link != NULL ) /* find last chain */
      tmp = tmp->link;
  tmp->link = chain;
done:
  return queue;
}

IOSIobuf *
IOS_PrequeueIob(IOSIobuf *queue, IOSIobuf *chain)
{
  if ( NULL == chain || (queue == chain) ) {
      printf("Prequeuing chain %p to queue %p failed\n", chain, queue);
      goto done;
  }
  chain->link = queue;
done:
  return chain;
}

u32
IOS_GetIobChainDataLen(IOSIobuf *iob)
{
  u32 len = 0;
  while ( iob != NULL ) {
      len += iob->dataLen;
      iob = iob->next;
  }
  return len;
}

u32
IOS_GetIobQueueLen(IOSIobuf *iob)
{
   u32 qlen = 0;
   while ( iob != NULL ) {
       ++qlen;
       iob = iob->link;
   }
   return qlen;
}

void
IOS_DebugDumpIobChain(IOSIobuf *iob)
{
    int i = 0;
    printf("Chain head: %p\n", iob);
    while ( NULL != iob) {
        printf("iob[%d] = %p ->\t", i++, iob);
        iob = iob->next;
        if (iob == NULL )
            printf("NULL\n");
    }
}

void
IOS_DebugDumpIobQueue(IOSIobuf *iob)
{
    int i = 0;
    printf("Queue head: %p Next queue: %p\n", iob, iob->link);
    while ( NULL != iob) {
        printf("chain %d: \n", i++);
        IOS_DebugDumpIobChain(iob);
        iob = iob->link;
    }
    printf("chain %d: NULL\n", i);
}
