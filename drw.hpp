/* See LICENSE file for copyright and license details. */

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

/* Because X.h loves to pollute the namespace */
#define Font NotXFont

struct Cur {
	Cursor cursor;
};

struct Font {
	Display* dpy;
	unsigned int h;
	XftFont* xfont;
	FcPattern* pattern;
	Font* next;
};

enum { ColFg, ColBg, ColCount }; /* Scheme index */
typedef XftColor* Scheme;

struct Draw {
	unsigned int w, h;
	Display* dpy;
	int screen;
	Window root;
	Drawable drawable;
	GC gc;
	Scheme scheme;
	Font* fonts;
};

/* Drawable abstraction */
Draw* drw_create(Display* dpy, int screen, Window win, unsigned int w, unsigned int h);
void drw_resize(Draw* drw, unsigned int w, unsigned int h);
void drw_free(Draw* drw);

/* Font abstraction */
Font* drw_fontset_create(Draw* drw, const char* fonts[], size_t fontcount);
void drw_fontset_free(Font* set);
unsigned int drw_fontset_getwidth(Draw* drw, const char* text);
void drw_font_getexts(Font* font, const char* text, unsigned int len, unsigned int* w, unsigned int* h);

/* Colorscheme abstraction */
void drw_clr_create(Draw* drw, XftColor* dest, const char* clrname);
Scheme drw_scm_create(Draw* drw, const char* clrnames[], size_t clrcount);

/* Cursor abstraction */
Cur* drw_cur_create(Draw* drw, int shape);
void drw_cur_free(Draw* drw, Cur* cursor);

/* Drawing context manipulation */
void drw_setfontset(Draw* drw, Font* set);
void drw_setscheme(Draw* drw, Scheme scm);

/* Drawing functions */
void drw_rect(Draw* drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
int drw_text(Draw* drw, int x, int y, unsigned int w, unsigned int h, unsigned int lpad, const char* text, int invert);

/* Map functions */
void drw_map(Draw* drw, Window win, int x, int y, unsigned int w, unsigned int h);

