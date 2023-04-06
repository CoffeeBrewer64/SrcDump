#!/usr/bin/python

import sys

bin = open(sys.argv[2]).read()
c = open(sys.argv[3], "w")
c.write("static unsigned char %s[] = {\n    " % sys.argv[1])
i = 0
prefix = ""
for x in bin:
  c.write("%s0x%02x" % (prefix, ord(x)))
  i = i + 1
  if i % 12 == 0:
    c.write("\n    ")
    prefix = ", "
  else:
    prefix = ", "
c.write("\n};")



