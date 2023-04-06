a22 33
static void
__acr_reg_test(void)
{
  IOSError rv;
  u8 flag = 0;
  u32 reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPOE_OFFSET);
  if (reg & GPIO_EEPROM_MASK) { /* try to clear if set */
      printf("Trying to clear GPIO_EEPROM_MASK %x\n", GPIO_EEPROM_MASK);
      reg &= ~GPIO_EEPROM_MASK;
      rv = IOS_ACRRegWrite(GPIIOPOE_OFFSET, reg);
      printf("ACRRegWrite returned: %d\n", rv);
      reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPOE_OFFSET);
      if (reg & GPIO_EEPROM_MASK) {
          flag = 1;
      } 
  } else {
      printf("Trying to set GPIO_EEPROM_MASK %x\n", GPIO_EEPROM_MASK);
      reg |= GPIO_EEPROM_MASK;
      rv = IOS_ACRRegWrite(GPIIOPOE_OFFSET, reg);
      printf("ACRRegWrite returned: %d\n", rv);
      reg = busRd32(ACR_PROT_REGS_BASE + GPIIOPOE_OFFSET);
      if ( 0 == (reg & GPIO_EEPROM_MASK)) {
          flag = 1;
      } 
  }
  if (1 == flag) {
      printf("PASSED. Write to EEPROM bit failed\n");
  } else {
      printf("FAILED. Write to EEPROM bit passed\n");
  }

}

a37 1
    __acr_reg_test();
