#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdlib.h>
#define BG_COLOR "#FF0000"

int main()
{
    Display *dis;
    Window root;
    XEvent ev;

    if (!(dis = XOpenDisplay(NULL))) return 1;
    root = DefaultRootWindow(dis);

    int screen_number = DefaultScreen(dis);

    Colormap colormap = DefaultColormap(dis, screen_number);

    XColor xcolor;
    XAllocNamedColor(dis, colormap, BG_COLOR, &xcolor, &xcolor);
    XSetWindowBackground(dis, root, xcolor.pixel);
    XClearWindow(dis, root);

    XSelectInput(dis, root, SubstructureRedirectMask | SubstructureNotifyMask);


    unsigned int modifiers[] = { 0, Mod2Mask, LockMask, Mod2Mask|LockMask };

    for (int i = 0; i < 4; i++) {
        XGrabKey(dis, XKeysymToKeycode(dis, XK_Return), Mod4Mask | modifiers[i], root,
                 True, GrabModeAsync, GrabModeAsync);
    }

    for (int i = 0; i < 4; i++) {
        XGrabKey(dis, XKeysymToKeycode(dis, XK_p), Mod4Mask | modifiers[i], root,
                 True, GrabModeAsync, GrabModeAsync);
    }

    XSync(dis, False);

    for (;;) {
        XNextEvent(dis, &ev);

        if (ev.type == MapRequest) {
            XMapWindow(dis, ev.xmaprequest.window);
            XRaiseWindow(dis, ev.xmaprequest.window);
        }
        else if (ev.type == KeyPress) {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);

            if (ks == XK_Return && (ev.xkey.state & Mod4Mask)) {
                system("alacritty &");
            }

            if (ks == XK_p && (ev.xkey.state & Mod4Mask)) {
                system("killall Xorg"); // makes me laugh every time :pray:
                break;
            }
        }
    }

    XCloseDisplay(dis);
    return 0;
}
