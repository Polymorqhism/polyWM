#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "config.h"

#define BG_COLOR "#090017"

void spawn_terminal() { system("alacritty &"); }
void quit() { system("killall Xorg"); }
void dmenu() { system("dmenu_run &"); }

int main()
{
    Display *dis;
    Window root;
    XEvent ev;

    if(!(dis = XOpenDisplay(NULL))) return 1;
    root = DefaultRootWindow(dis);

    for(int i = 0; i<LENGTH(keys); i++) {
        grab_key(dis, root, keys[i].key, keys[i].mod);
    }

    Cursor cursor = XCreateFontCursor(dis, XC_left_ptr);
    XDefineCursor(dis, root, cursor);

    int screen_number = DefaultScreen(dis);

    Colormap colormap = DefaultColormap(dis, screen_number);

    XColor xcolor;
    XAllocNamedColor(dis, colormap, BG_COLOR, &xcolor, &xcolor);
    XSetWindowBackground(dis, root, xcolor.pixel);
    XClearWindow(dis, root);

    XSelectInput(dis, root, SubstructureRedirectMask | SubstructureNotifyMask);


    unsigned int modifiers[] = { 0, Mod2Mask, LockMask, Mod2Mask|LockMask };

    XSync(dis, False);

    for(;;) {
        XNextEvent(dis, &ev);

        if(ev.type == MapRequest) {
            XSelectInput(dis, ev.xmaprequest.window, EnterWindowMask);
            XMapWindow(dis, ev.xmaprequest.window);
            XSetInputFocus(dis, ev.xmaprequest.window, RevertToPointerRoot, CurrentTime);
            XRaiseWindow(dis, ev.xmaprequest.window);
        }

        else if(ev.type == KeyPress) {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);
            // handles key
            for(int i = 0; i<LENGTH(keys); i++) {
                if(ks == keys[i].key && (ev.xkey.state & keys[i].mod)) { // deadass no idea what this does it just works
                    keys[i].handler();
                }
            }
        }

        else if(ev.type == EnterNotify) {
            XSetInputFocus(dis, ev.xcrossing.window, RevertToPointerRoot, CurrentTime);
        }
    }

    XFreeCursor(dis, cursor);
    XCloseDisplay(dis);
    return 0;
}
