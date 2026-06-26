#include "globals.h"
#include "util/util.h"
#include "config.h"

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))

int main()
{

    if(!(dis = XOpenDisplay(NULL))) return 1;
    screen_number = DefaultScreen(dis);
    root = DefaultRootWindow(dis);


    Cursor cursor = XCreateFontCursor(dis, XC_left_ptr);
    XDefineCursor(dis, root, cursor);


    Colormap colormap = DefaultColormap(dis, screen_number);

    XAllocNamedColor(dis, colormap, "BLACK", &xcolor, &xcolor);
    XSetWindowBackground(dis, root, xcolor.pixel);

    XFontStruct *font = XLoadQueryFont(dis, "fixed");
    gc = XCreateGC(dis, root, 0, NULL);
    XSetFont(dis, gc, font->fid);
    XSetForeground(dis, gc, WhitePixel(dis, screen_number));
    XClearWindow(dis, root);


    width = XDisplayWidth(dis, screen_number);
    height = XDisplayHeight(dis, screen_number);

    XSync(dis, False);

    XSelectInput(dis, root, KeyPressMask | SubstructureRedirectMask);

    for(int i = 0; i<LENGTH(keys); i++) {
        grab_key(dis, root, keys[i].key, keys[i].mod);
    }

    for(;;) {
        XNextEvent(dis, &ev);

        if(ev.type == KeyPress) {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);
            // handles key
            for(int i = 0; i<LENGTH(keys); i++) {
                if(ks == keys[i].key && (ev.xkey.state & keys[i].mod)) {
                    keys[i].handler(&keys[i].arg);
                }
            }
        }

        else if(ev.type == MapRequest) {
            XMapWindow(dis, ev.xmaprequest.window);
            XSetInputFocus(dis, ev.xmaprequest.window, RevertToPointerRoot, CurrentTime);
        }
    }


    XFreeCursor(dis, cursor);
    XCloseDisplay(dis);
}
