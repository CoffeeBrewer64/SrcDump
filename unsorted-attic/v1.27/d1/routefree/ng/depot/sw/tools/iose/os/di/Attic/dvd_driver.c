d1 1
a1 1
#ident "$Id: dvd_driver.c,v 1.26 2006/02/17 02:06:42 craig Exp $"
d413 2
a414 3
        tmpVal = readDICoverReg();
        DICoverReg &= ~DI_COVER_INTR_MASK;
        tmpVal     &= ~DI_COVER_INTR_MASK;
d419 2
a420 3
        tmpVal = readDICoverReg();
        DICoverReg |= DI_COVER_INTR;
        tmpVal     |= DI_COVER_INTR;
d425 2
a426 3
        tmpVal = readDICoverReg();
        DICoverReg |= DI_COVER_INTR_MASK;
        tmpVal     |= DI_COVER_INTR_MASK;
