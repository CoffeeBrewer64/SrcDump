set CLASSPATH=.\java\mvmsg
java mvmsg .\source\*.dmg
set CLASSPATH=
copy .\source\*.dmg0 .\source\temp2
del .\source\*.dmg0
rename .\source\temp2\*.dmg0 *.dmg
copy i_msg2_?.dmg .\source\temp2
del i_msg2_?.dmg
