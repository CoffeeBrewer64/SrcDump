d1 1
a1 1
#ident "$Id: rvl_image.c,v 1.8 2006/03/17 22:19:12 craig Exp $"
d14 5
a18 1
 * Program to generate RVL secure DVD images.  See the Powerpoint
d124 3
d135 1
a135 1
static bool     Verbose;
d144 1
d172 4
d238 3
d246 60
d791 4
a794 1
    off_t       endOfImage;
d805 2
d823 7
d835 1
a835 1
}
d943 2
a944 1
        if (copyFileToOutFile(outFile, inputDisk->inputUpdateAreas[i]->content) == false) {
d1018 2
d1631 34
