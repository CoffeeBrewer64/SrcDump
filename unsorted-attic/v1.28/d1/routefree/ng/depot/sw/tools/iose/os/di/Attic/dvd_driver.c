d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.27 2006/02/18 00:39:41 craig Exp $"
d39 1
d137 1
a137 1
            printf ("Receiving OPEN request\n");
d139 1
a139 1
            printf ("(dvd_driver) Open returns: %d\n", returnStatus);
d144 1
a144 1
            printf ("Receiving CLOSE request (%d/0x%x)\n",
d163 1
a163 1
            printf ("Note: Transaction done message in main DVD loop.\n");
d171 1
a171 1
            printf("Note: Transaction error message in main DVD loop.\n");
d176 1
a176 1
                printf ("Received cover interrupt message!\n");
d184 8
a191 3
            printf ("Unknown message type (0x%x) received.\n",
                     inMesg.otherMesg->mesgType);
            break;
d335 1
a335 1
            printf ("(DiOpen) returning 0x%x (i=%d)\n",
d409 1
a409 1
        printf ("(DiIoctl) Reading Immediate Reg; val = 0x%x\n",
d434 1
a434 1
        printf ("++++ (DiIoctl) Cover Reg; val = 0x%x\n", DICoverReg);
d453 1
a453 1
            printf ("+++ DOING READ WITHOUT DECRYPT +++\n");
d496 5
