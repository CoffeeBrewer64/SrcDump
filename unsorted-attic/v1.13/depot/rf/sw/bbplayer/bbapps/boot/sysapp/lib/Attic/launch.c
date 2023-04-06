a23 1
                   u32 *haveCrl,
d32 1
a32 1
    int i;
a34 2
    *haveCrl=1;

d91 2
a92 1
        *haveCrl = 0;
d94 1
a94 1
    if(*haveCrl){
a138 1
    u32 haveCrl;
d145 1
a145 2
    if(BB_SYSAPP_PASS != saBundleTicket(ticket,
                                        &ticketBundle,&appRls,&haveCrl,
d151 1
a151 3
    if(SK_API_SUCCESS != skLaunchSetup(&ticketBundle, 
                                  haveCrl ? &appRls : (void *)0, 
                                  keyList)){
