d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.7 2006/03/15 02:54:05 craig Exp $"
a198 16
#ifdef NOT_DONE
inline void *
copyStructure(const void* const struct, const size_t struct_size)
{
    void        *returnVal;

    returnval = malloc (struct_size);
    if (returnval == NULL) {
        fprintf (stderr, "Error: malloc returned NULL - exit\n");
        exit(1);
    }
}
#endif

/* ------------------------------------------------------------------------ */

d687 4
