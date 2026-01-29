#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

extern int WORKSPACES;
extern char buf[64];
extern int width, height;
extern int current_workspace;
extern Window windows[][2];
extern int win_count[];
extern Display *dis;
extern Window root;
extern XEvent ev;
extern GC gc;
extern XColor xcolor;
extern int screen_number;
