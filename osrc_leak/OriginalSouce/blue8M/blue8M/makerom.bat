set CLASSPATH=\users\java\makerom
java makerom .\source\debug\bluemons.isx bluemons.bin bluemons.sdb
set CLASSPATH=
copy bluemons.bin .\source\bin
del bluemons.bin
