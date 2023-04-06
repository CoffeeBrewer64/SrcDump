d2 1
a2 1
Date: 12/02/2009
d28 2
a29 5
   9) ES Resource Manager
      * Only object files (*.o) are provided but can be used to build ES RM
        using a different address map.
  10) DI Resource Manager
  11) SDI Resource Manager
d91 1
a91 3
                 - Source to build DI RM.
              - es/
                 - Object files, link file and Makefile to build ES RM.
d93 1
a93 1
                 - Source to build ISFS RM.
d99 1
a99 1
                 - Source to build SDI RM.
d118 7
a124 6
   - Type the followings to build libraries and programs AND installing them
     to $ROOT/usr/lib/rvl and $ROOT/usr/bin/rvl:
       * make clobber
       * make headers
       * make exports
       * make install
