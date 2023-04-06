d14 3
d21 3
d1176 1
a1176 1
        IFDequeueItem(IPInfo*, &prev->queueNext, info, linkNext);
d1182 1
a1182 1
        IFEnqueueTail(IPInfo*, &entry->queueNext, info, linkNext);
d1196 1
a1196 1
        IFDequeueItem(IPInfo*, &prev->queueNext, info, linkNext);
d1202 1
a1202 1
        IFEnqueueTail(IPInfo*, &entry->queueNext, info, linkNext);
