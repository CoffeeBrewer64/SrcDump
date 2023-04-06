#!/usr/bin/python

import sys, os, string, struct

global crc_table

crc_table = range(256)
def make_crc_table():
    p = (0,1,2,4,5,7,8,10,11,12,16,22,23,26)

    poly = 0
    for n in p:
      poly = poly | (1L << (31 - n))

    for n in range(256):
      c = n
      for k in range(8):
        if c & 1:
          c = poly ^ (c >> 1L)
        else:
          c = c >> 1L
      crc_table[n] = c

def crc32(op, crc):
  crc = crc ^ 0xffffffffL
  crc = crc_table[(crc ^ ((op >>  0)&0xff)) & 0xff] ^ (crc >> 8);
  crc = crc_table[(crc ^ ((op >>  8)&0xff)) & 0xff] ^ (crc >> 8);
  crc = crc_table[(crc ^ ((op >> 16)&0xff)) & 0xff] ^ (crc >> 8);
  crc = crc_table[(crc ^ ((op >> 24)&0xff)) & 0xff] ^ (crc >> 8);
  return crc ^ 0xffffffffL

prefix = ""
signatures = {}
relocations = {}
reloc_symbols = {}
crcs = {}

def compute_sig(obj, symbol, relocs):
  num_bytes = symbol["len"]
  offset = symbol["offset"]
  instructions = struct.unpack(">" + "l" * (num_bytes>>2), obj[offset:offset+num_bytes])
  crc = 0
  partial_crc = 0
  i = offset
  hi_delta = 0
  lo_delta = 0
  mask = 0xffffffff
  for inst in instructions:
    op = inst
    if relocs.has_key(i):
      if relocs[i]["type"] == "R_MIPS_26":
        hi_delta = op & 0x03ffffff
        op = op & 0xfc000000
        if i == offset: mask = 0xfc000000
      else:
        if relocs[i]["type"] == "R_MIPS_HI16":
          hi_delta = op & 0x0000ffff
        else:
          lo_delta = op & 0x0000ffff
        op = op & 0xffff0000
        if i == offset: mask = 0xffff0000
      if not relocations.has_key(symbol["name"]):
        relocations[symbol["name"]] = [symbol["file"]]
      relocations[symbol["name"]].append(((i-offset)>>2, hi_delta, lo_delta, relocs[i]["type"], relocs[i]["symbol"]))
    else:
      if ((op >> 26) & 0x3f) == 2: # J instruction
        op = op & 0xfc000000
    crc = crc32(op, crc)
    if ((i-offset) < 16):
      partial_crc = crc
    i = i + 4
  d = {}
  d["num_ops"] = len(instructions)
  d["first_op"] = instructions[0] & mask
  d["first_mask"] = mask
  d["partial_crc"] = partial_crc
  d["crc"] = crc
  d["file"] = symbol["file"]
  signatures[symbol["name"]] = d
  try:
    crcs[crc].append(symbol["name"])
  except KeyError:
    crcs[crc] = [symbol["name"]]

def extract_doto(archive, doto):
  #sys.stderr.write("Extracting '%s'\n" % doto)
  res = os.system("ar x %s %s" % (archive, doto))
  #sys.stderr.write("  res = %d\n" % res)
  os.chmod(doto, 0400)

def extract_symbols(doto):
  symbol_table = os.popen("readelf -s %s" % doto).readlines()
  symbols = []
  for sym in symbol_table:
    l = string.split(sym)
    if len(l) == 8 and l[3] == 'FUNC' and l[6] != 'UND' and l[2] != '0':
      d = {}
      d["name"] = l[7]
      d["offset"] = string.atoi(l[1], 16)
      d["len"] = string.atoi(l[2])
      d["file"] = doto
      symbols.append(d)
  return symbols

def extract_relocs(doto):
  reloc_lines = os.popen("readelf -r %s" % doto).readlines()
  relocs = {}
  for l in reloc_lines:
    r = string.split(l)
    if len(r) == 5:
      if r[2] != "R_MIPS_HI16" and r[2] != "R_MIPS_LO16" and r[2] != "R_MIPS_26" or (r[4][0] == "." and r[4] != '.text' and r[4] != '.rodata'):
        continue
      d = {}
      d["type"] = r[2]
      d["symbol"] = r[4]
      reloc_symbols[r[4]] = 1
      relocs[string.atoi(r[0], 16)] = d
  return relocs

def get_text_offset(doto):
  sections = os.popen("readelf -S %s | cut -c 8-" % doto).readlines()
  offset = 0
  for s in sections:
    l = string.split(s)
    if len(l) > 0 and l[0] == ".text":
      offset = string.atoi(l[3], 16)
      break
  return offset

def dump_signatures():
  keys = signatures.keys()
  keys.sort()
  print 'sig_t %s_sigs[] = {' % prefix
  for key in keys:
    s = signatures[key]
    if s['num_ops'] < 3:
      continue
    r = "NULL"
    if relocations.has_key(key):
      r = "%s_%s_relocs" % (prefix, key)
    print '    {"%s", %d, %#08x, %#08x, %#08x, %#08x, 0, %s, %d}, /* %s */' % (key, s['num_ops'], s['first_op'], s['first_mask'], s['crc'], s['partial_crc'], r, len(crcs[s['crc']]) > 1, s['file'])
  print '    {0, 0, 0, 0, 0, 0, 0, 0} /* sentinel */'
  print '};'

def dump_relocations():
  keys = relocations.keys()
  keys.sort()
  for key in keys:
    l = relocations[key]
    print 'rel_t %s_%s_relocs[] = { /* %s */' % (prefix, key, l[0])
    for r in l[1:]:
      if r[4] != '.text' and r[4] != '.rodata':
        print '    {%s, %s, %s, %s, &%s_%s_sym, 0},' % (r[0], r[1], r[2], r[3], prefix, r[4])
      else:
        if r[4] == '.text':
          print '    {%s, %s, %s, %s, NULL, 1},' % (r[0], r[1], r[2], r[3])
        else:
          print '    {%s, %s, %s, %s, NULL, 0},' % (r[0], r[1], r[2], r[3])
    print '    {0, 0, 0, R_MIPS_26, NULL, 0}'
    print '};'

def dump_reloc_symbols():
  l = reloc_symbols.keys()
  l.sort()
  for s in l:
    if s == '.text' or s == '.rodata':
      continue
    if signatures.has_key(s):
      size = signatures[s]['num_ops']*4
    else:
      size = 4
    print 'sym_t %s_%s_sym = {"%s", 0, 0, 0, %d};' % (prefix, s, s, size)

  print 'sym_t %s__osBbEepromAddress_sym = {"__osBbEepromAddress", 0x8000, 0x035c, 1, 4};' % prefix
  print 'sym_t %s__osBbEepromSize_sym = {"__osBbEepromSize", 0x8000, 0x0360, 1, 4};' % prefix
  print 'sym_t %s__osBbFlashAddress_sym = {"__osBbFlashAddress", 0x8000, 0x0364, 1, 4};' % prefix
  print 'sym_t %s__osBbFlashSize_sym = {"__osBbFlashSize", 0x8000, 0x0368, 1, 4};' % prefix
  print 'sym_t %s__osBbFlashBuffer_sym = {"__osBbFlashBuffer", 0x8070, 0x4000, 1, 128};' % prefix
  print 'sym_t %s__osBbSramAddress_sym = {"__osBbSramAddress", 0x8000, 0x036c, 1, 4};' % prefix
  print 'sym_t %s__osBbSramSize_sym = {"__osBbSramSize", 0x8000, 0x0370, 1, 4};' % prefix
  print 'sym_t %s__osBbPakAddress_sym = {"__osBbPakAddress", 0x8000, 0x0374, 1, 4};' % prefix
  print 'sym_t %s__osBbPakSize_sym = {"__osBbPakSize", 0x8000, 0x0378, 1, 4};' % prefix
  print 'sym_t %s__osBbIsBb_sym = {"__osBbIsBb", 0x8000, 0x037c, 1, 4};' % prefix
  print 'sym_t %s__osBbHackFlags_sym = {"__osBbHackFlags", 0x8000, 0x0380, 1, 4};' % prefix
  print 'sym_t %s__osMemSize_sym = {"osMemSize", 0x8000, 0x0318, 1, 4};' % prefix

  print 'sym_t *%s_syms[] = {' % prefix
  for s in l:
    if s == '.text' or s == '.rodata':
      continue
    print '  &%s_%s_sym,' % (prefix, s)
  print '&%s__osBbPakSize_sym,' % prefix
  print '&%s__osBbPakAddress_sym,' % prefix
  print '&%s__osBbEepromAddress_sym,' % prefix
  print '&%s__osBbEepromSize_sym,' % prefix
  print '&%s__osBbFlashAddress_sym,' % prefix
  print '&%s__osBbFlashSize_sym,' % prefix
  print '&%s__osBbFlashBuffer_sym,' % prefix
  print '&%s__osBbSramAddress_sym,' % prefix
  print '&%s__osBbSramSize_sym,' % prefix
  print '&%s__osBbIsBb_sym,' % prefix
  print '&%s__osBbHackFlags_sym,' % prefix
  print '&%s__osMemSize_sym,' % prefix
  print '  NULL\n};'


def main(argv):
  make_crc_table()
  archive = argv[1]
  global prefix
  prefix = string.split(string.split(archive, '.')[0], '/')[-1]
  ofiles = string.split(os.popen("ar t %s" % archive).read())
  for doto in ofiles:
    extract_doto(archive, doto)
    symbols = extract_symbols(doto)
    relocs = extract_relocs(doto)
    offset = get_text_offset(doto)
       
    if offset != 0:
      obj = open(doto).read()[offset:]
      for sym in symbols:
        compute_sig(obj, sym, relocs)
  
    os.unlink(doto)
  dump_reloc_symbols()
  dump_relocations()
  dump_signatures()

if __name__ == '__main__':
  main(sys.argv)
