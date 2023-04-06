d83 1
d85 1
d94 1
a94 1
static char* options = "ho:t:Vv";
d111 2
a112 1
                 char *titleKeyName);
d119 4
a122 1
                       const uint32_t titleId);
d134 1
d136 1
d159 2
a160 1
               char **outputName, uint32_t *titleId)
d165 4
a168 2
    *outputName = NULL;
    *titleId = 0xdead;
d182 4
d191 4
d228 1
a228 1
}
d235 1
d240 2
a241 1
    processOptions(argc, argv, &contentName, &outputFileName, &titleId);
d243 2
a244 1
    if (generatePartition(contentName, outputFileName, titleId) == false) {
d443 2
a444 1
            char* h3HashName, char* titleKeyName)
d458 8
d570 5
a574 2
generatePartition(const char* const contentName, const char* const outputName,
                  const uint32_t titleId)
d596 2
a597 1
                    h3HashName, titleKeyName) == false) {
