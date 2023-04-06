#!/usr/bin/python

import sys, re


header = """/*
 *               Copyright (C) 2005, BroadOn Communications Corp.
 *
 *  These coded instructions, statements, and computer programs contain
 *  unpublished  proprietary information of BroadOn Communications Corp.,
 *  and  are protected by Federal copyright law. They may not be disclosed
 *  to  third  parties or copied or duplicated in any form, in whole or in
 *  part, without the prior written consent of BroadOn Communications Corp.
 *
 */

/* This file automatically generated -- Do not edit */
#include <sktypes.h>
#include <sk.h>

"""

footer = """
"""
def parse_syscalls(name):
  f = open(name)
  calls = []
  for l in f.readlines():
    l = l.strip()
    if l != "":
      result = re.match('([a-zA-Z0-9_]*\s*\**)([^(]*)\((.*)\)', l)
      ret = result.group(1)
      func = result.group(2)
      params = result.group(3)
      param_notyp = ""
      for p in result.group(3).split(','):
        if  p != "void" :
          res = ""
          result0 = re.match('([a-zA-Z0-9_]*\s*[a-zA-Z0-9_]*\s*)(\**)(.*)', p.strip())
          result1 = re.match('([a-zA-Z0-9_]*\s*) (\**)(.*)', p.strip())
          if result0 :
            res = result0.group(result0.lastindex)
          if res == "" :  
            res = result1.group(result1.lastindex)
          param_notyp += res
        param_notyp += ","

      param_notyp = param_notyp.strip(',')
      calls.append((ret, func, params, param_notyp));
  return calls

if __name__ == "__main__":
  calls = parse_syscalls(sys.argv[1])
  out = open(sys.argv[3], "w")
  out.write(header)
  for call in calls:
    s = "extern %s sk%s(%s);\n" % (call[0], call[1], call[2])
    out.write(s + '\n')
    s = "%s SK_%s(%s) \n {\n return sk%s(%s);\n}\n" % (call[0], call[1], call[2], call[1], call[3])
    out.write(s + '\n')
 
  print(sys.argv[2])
  calls = parse_syscalls(sys.argv[2])
  for call in calls:
    s = "extern %s usb%s(%s);\n" % (call[0], call[1], call[2])
    out.write(s + '\n')
    s = "%s IUSB_%s(%s) \n {\n return usb%s(%s);\n}\n" % (call[0], call[1], call[2], call[1], call[3])
    out.write(s + '\n')

  out.write(footer)
  out.close()
