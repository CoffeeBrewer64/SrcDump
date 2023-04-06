#!/bin/csh

/bin/touch compile.command_log
/bin/rm    compile.command_log

/bin/touch compile.summary
/bin/rm    compile.summary*

/bin/touch db
/bin/rm -r db
/bin/mkdir db

/bin/touch gate
/bin/rm -r gate
/bin/mkdir gate

/bin/touch report
/bin/rm -r report
/bin/mkdir report

/bin/touch .synopsys_dc.setup
/bin/rm    .synopsys_dc.setup
ln -s ../SCRIPT_COMMON/synopsys_dc.setup .synopsys_dc.setup


echo "======================================"
set dir = `pwd`
echo $dir | sed -e s/'.*\/'//g | sed -e s/'^'/"   Synthesize : "/g

#----------------------------------

echo "----------------------------"
echo "         DC start"
date
echo "----------------------------"

set os = `uname -s`

if ( $os == "Linux" || $os == "linux" ) then

/app/synopsys/v2001.08-SP1-2/linux/syn/bin/dc_shell << ! > compile.summary
   include ./script/compile.scr
!
../SCRIPT_COMMON/mod_summary.Linux compile.summary > compile.summary_mod

else

/app/synopsys/v2001.08-SP1-2/sparcOS5/syn/bin/dc_shell << ! > compile.summary
   include ./script/compile.scr
!
../SCRIPT_COMMON/mod_summary.SunOS compile.summary > compile.summary_mod

endif


echo "         DC finish"
date
echo "----------------------------"


mv compile.summary_mod compile.summary
grep Error compile.summary
grep Can   compile.summary
egrep 'Timing.*loop'  compile.summary
egrep 'assign.*tran' compile.summary
set block = `pwd | sed -e s/'.*\/'//g`
mv compile.summary compile.summary.$block


FV.com


