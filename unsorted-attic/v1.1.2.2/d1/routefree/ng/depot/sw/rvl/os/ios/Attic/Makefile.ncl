d8 4
a11 1
# Targets
d13 2
d16 1
d18 1
d20 1
d28 3
a30 3
OS_TARGETS = $(OS) $(OS_REAL) $(OS_PROFILE) $(BOOT2_OS_REAL) \
             $(PROD_OS_REAL) $(PROD_BOOT2_OS_REAL)

d222 1
a222 1
# Real image with crypto and shell
d224 14
a237 2
$(OS): $(CRYPTO_LINKER_FILE) crypto_objs cslrsa_dev.o shell_objs $(CRYPTO_OBJS)
	$(CC) $(CFLAGS) -o $(OS) $(CRYPTO_OBJS) crypto_tmp/*.o shell_tmp/*.o $(LDFLAGS) $(LDLIBS) -T $(CRYPTO_LINKER_FILE)
d244 4
d263 5
