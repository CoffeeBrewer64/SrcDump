d10 6
a15 1
#define	BMP_DATA	0
a27 1
#define BGCOLOR		0x0000
a34 7
#define	FBUF_ADRS(x,y)		(FBUF_TOP+((x)+(y)*SCREEN_WD)*2)
#define	canvas_cursor(x,y)	__cursor = (u16 *)FBUF_ADRS((x),(y))
#define	canvas_center(x,y)	canvas_cursor((SCREEN_WD-(x)*FONT_WSKIP)/2,(y))
#define	canvas_wskip(x)		__cursor += (x);
#define	canvas_putstr(n,fg,bg)	canvas_puts((n), sizeof(n)-1, (fg), (bg))


d47 1
a47 8
extern	void	WriteBG(u8 *, u16 *);
extern	void	SetBG(u8 *, u16 *);
extern	void	gputchar(u16, int, int, char, u16 *);
extern	void	gprintstr(u16, int, int, char*, u16 *);


extern	u16	*__cursor;
extern	u16	__color;
