d155 1
d164 5
a168 1
    print 'sym_t %s_%s_sym = {"%s", 0, 0, 0};' % (prefix, s, s)
d170 10
a179 10
  print 'sym_t %s__osBbEepromAddress_sym = {"__osBbEepromAddress", 0x8000, 0x035c, 1};' % prefix
  print 'sym_t %s__osBbEepromSize_sym = {"__osBbEepromSize", 0x8000, 0x0360, 1};' % prefix
  print 'sym_t %s__osBbFlashAddress_sym = {"__osBbFlashAddress", 0x8000, 0x0364, 1};' % prefix
  print 'sym_t %s__osBbFlashSize_sym = {"__osBbFlashSize", 0x8000, 0x0368, 1};' % prefix
  print 'sym_t %s__osBbSramAddress_sym = {"__osBbSramAddress", 0x8000, 0x036c, 1};' % prefix
  print 'sym_t %s__osBbSramSize_sym = {"__osBbSramSize", 0x8000, 0x0370, 1};' % prefix
  print 'sym_t %s__osBbPakAddress_sym = {"__osBbPakAddress", 0x8000, 0x0374, 1};' % prefix
  print 'sym_t %s__osBbPakSize_sym = {"__osBbPakSize", 0x8000, 0x0378, 1};' % prefix
  print 'sym_t %s__osBbIsBb_sym = {"__osBbIsBb", 0x8000, 0x037c, 1};' % prefix
  print 'sym_t %s__osBbHackFlags_sym = {"__osBbHackFlags", 0x8000, 0x0380, 1};' % prefix
