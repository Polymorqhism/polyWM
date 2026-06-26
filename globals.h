#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <string.h>
#include <X11/cursorfont.h>

extern Display *dis;
extern int height;
extern int width;
extern Window root;
extern XEvent ev;
extern GC gc;
extern XColor xcolor;
extern int screen_number;
