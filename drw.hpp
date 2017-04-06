/* See LICENSE file for copyright and license details. */

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

/* Because X.h loves to pollute the namespace */
#define Font NotXFont

typedef Cursor XCursor;
#define Cursor NotXCursor

typedef Drawable XDrawable;
#define Drawable NotXDrawable

struct Cursor {
	XCursor cursor;
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

/* Drawableable abstraction */
struct Drawable {
	unsigned int w, h;
	Display* dpy;
	int screen;
	Window root;
	XDrawable drawable;
	GC gc;
	Scheme scheme;
	Font* fonts;
	
	Drawable(Display* dpy, int screen, Window win, unsigned w, unsigned h);
	
	~Drawable();
	
	void resize(unsigned int w, unsigned int h);
};

/* Drawableable abstraction */
__attribute__((deprecated))
Drawable* drw_create(Display* dpy, int screen, Window win, unsigned int w, unsigned int h);
__attribute__((deprecated))
void drw_resize(Drawable* drw, unsigned int w, unsigned int h);
__attribute__((deprecated))
void drw_free(Drawable* drw);

/* Font abstraction */
Font* drw_fontset_create(Drawable* drw, const char* fonts[], size_t fontcount);
void drw_fontset_free(Font* set);
unsigned int drw_fontset_getwidth(Drawable* drw, const char* text);
void drw_font_getexts(Font* font, const char* text, unsigned int len, unsigned int* w, unsigned int* h);

/* Colorscheme abstraction */
void drw_clr_create(Drawable* drw, XftColor* dest, const char* clrname);
Scheme drw_scm_create(Drawable* drw, const char* clrnames[], size_t clrcount);

/* Cursor abstraction */
Cursor* drw_cur_create(Drawable* drw, int shape);
void drw_cur_free(Drawable* drw, Cursor* cursor);

/* Drawableing context manipulation */
void drw_setfontset(Drawable* drw, Font* set);
void drw_setscheme(Drawable* drw, Scheme scm);

/* Drawableing functions */
void drw_rect(Drawable* drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
int drw_text(Drawable* drw, int x, int y, unsigned int w, unsigned int h, unsigned int lpad, const char* text, int invert);

/* Map functions */
void drw_map(Drawable* drw, Window win, int x, int y, unsigned int w, unsigned int h);

