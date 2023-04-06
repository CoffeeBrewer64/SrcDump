#!/bin/csh

set cell = `ls ./gate/*.g.v | sed -e s/'.*\/'//g | sed -e s/'\.g\.v'//g`

/bin/touch  fv
/bin/rm -rf fv

set os = `uname -s`
if ( $os == "Linux" || $os == "linux" ) then
echo "-----------------------------------"
echo "$cell"
echo "Formality : NOT executed on linux !"
echo "-----------------------------------"
exit
endif

/bin/mkdir  fv
cd          fv

/bin/touch  .synopsys_fm.setup
/bin/rm -rf .synopsys_fm.setup
ln -s ../../SCRIPT_COMMON/synopsys_fm.setup .synopsys_fm.setup

grep 'read .*verilog' ../script/read_verilog.scr |\
sed -e s/'\/\*.*\*\/'//g |\
grep 'read .*verilog' |\
sed -e s/'.* verilog '//g |\
sed -e s/'.*\/RTL\/'//g |\
awk '{ print "../../../RTL/" $0}' |\
sort -u |\
egrep -v '^nv' |\
egrep -v '^nms' |\
cat > list_rtl

grep 'include' ../script/* |\
grep "read_jlib.scr" |\
sed -e s/'\/\*.*\*\/'//g |\
sort -u |\
cat > temp.jlib
set jlib = `wc temp.jlib | awk '{print $1}'`

if ($jlib == "1") then
grep 'read .*verilog' ../../SCRIPT_COMMON/read_jlib.scr |\
sed -e s/'\/\*.*\*\/'//g |\
grep 'read .*verilog' |\
sed -e s/'.* verilog '//g |\
awk '{ print "../../../RTL/" $0}' |\
sort -u |\
cat >> list_rtl
endif


echo "#\!/bin/csh -f" > list_rtl_catshell
echo "/bin/touch  RTL.v" >> list_rtl_catshell
echo "/bin/rm -rf RTL.v" >> list_rtl_catshell
cat list_rtl |\
awk '{ print "cat " $0 " >> RTL.v"}' |\
cat >> list_rtl_catshell
chmod 755 list_rtl_catshell
list_rtl_catshell


  cat ../../SCRIPT_COMMON/hina.fv |\
  sed -e s/"%CELLNAME%"/$cell/g |\
  cat > $cell.fv


echo "----------------------------"
echo " $cell"
echo "      Formality start"
date
echo "----------------------------"

 /app/synopsys/FM2001.08-SP1/sparcOS5/fm/bin/fm_shell -file $cell.fv |\
 sed -e s/"formality.log"/$cell.log/g |\
 cat > $cell.result

echo "      Formality finish"
date
echo "----------------------------"

  mv fm_shell_command.log $cell.shell_command
  mv formality.log $cell.log
 
/bin/rm -rf temp.jlib
/bin/rm -rf list_rtl_catshell

grep Error $cell.result
echo "see $cell/fv/$cell.result & $cell.log"
echo "----------------------------"

cd ..
