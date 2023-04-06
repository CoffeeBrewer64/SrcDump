a7 1
#include	"nu64sys.h"
d12 16
a27 5
#if	BMP_DATA
#include	"bmpdata.c"
#endif

u16	__color;
a327 3
#if	BMP_DATA
    *p++ = bmpdata[i];
#else
a328 54
#endif
  }
}

/*---------------------------------------------------------------------
                  Set Graphic data to tmp buffer 
  ---------------------------------------------------------------------*/
void
SetBG(u8 *gr, u16 *gbuf)
{
  int 	i, j;

  for (i = 0, j = 0 ; i < SCREEN_WD*SCREEN_HT ; i ++ , j += 3) {
    *gbuf++ = GPACK_RGBA5551(gr[j],  gr[j + 1], gr[j + 2], 1);
  }
}

/*---------------------------------------------------------------------
                  Write Graphic data to buffer from tmp buffer
  ---------------------------------------------------------------------*/
void
WriteBG(u8 *gr, u16 *gbuf)
{
  int 	i;
  u16	*p;

  p = (u16 *)osViGetNextFramebuffer();
  for (i = 0 ; i < SCREEN_WD*SCREEN_HT ; i ++ ) {
    *p++ = *gbuf++;
  }
}

/*---------------------------------------------------------------------
                  Display character on the tmp buffer
  ---------------------------------------------------------------------*/
void
gputchar(u16 color, int curs_x, int curs_y, char c, u16 *buf)
{
  int	i, j;
  int	x = curs_x*CHAR_WD;
  int	y = curs_y*CHAR_HT;
  u8	*pc = pat[c-0x20];
  u16	*p = buf + x + SCREEN_WD*(y-8);

  for (j = 0; j < CHAR_HT; j ++, pc++) {
    for (i = CHAR_WD - 1; i >= 0; i --) {
      if (*pc & (1 << i)) {
	*p = color;
      } else {
	*p = BGCOLOR;
      }
      p ++;
    }
    p += SCREEN_WD - CHAR_WD;
a331 3
/*---------------------------------------------------------------------
                  Display string on the tmp buffer
  ---------------------------------------------------------------------*/
d333 1
a333 1
gprintstr(u16 color, int curs_x, int curs_y, char *s, u16 *buf)
d335 1
a335 5
    int i;

    for (i = 0; *s != NULL; i ++) {
      gputchar(color, curs_x+i, curs_y, *s++, buf);
    }
a336 2


