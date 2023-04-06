d1 1
a1 1
#ident "$Id: usbeth_boot.c,v 1.5 2006/05/09 00:54:36 psmith Exp $"
d19 1
a19 1
#define NPKT 1
a59 2
static IOSIobDebugInfo iobufDebugInfo;

a78 1
//    IOSIobuf * iob;
d86 1
a99 1
        printf ("open returned rv = %d\n",rv);
d104 1
d106 1
d119 1
d121 1
d131 1
d133 1
a133 1
//            printf ("NET_DEV_UP, rv = %d\n",rv);
d152 1
a152 1
                IOS_IOB_INCREF(txIob);
d154 1
d161 1
d163 1
d168 1
d170 1
a170 1
//            printf ("NET_DEV_DOWN, rv = %d\n",rv);
a177 1
        printf("close returned rv = %d\n",rv);
