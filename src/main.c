#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))


int main()
{
    Display *dis;
    int screen;
    Window win;
    GC gc;

    if(!(dis = XOpenDisplay(0x0))) return 1;
}


