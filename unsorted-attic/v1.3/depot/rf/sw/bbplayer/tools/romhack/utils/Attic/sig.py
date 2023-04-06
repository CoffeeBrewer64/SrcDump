d47 1
d54 1
d61 1
d74 2
a75 1
  d["first_op"] = (instructions[0] >> 26) & 0x3f
d141 2
a142 2
    print '    {"%s", %d, %d, %#08x, %#08x, 0, %s, %d}, /* %s */' % (key, s['num_ops'], s['first_op'], s['crc'], s['partial_crc'], r, len(crcs[s['crc']]) > 1, s['file'])
  print '    {0, 0, 0, 0, 0, 0, 0} /* sentinel */'
d185 1
d203 1
