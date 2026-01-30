#include <X11/Xlib.h>
#include <string.h>
#include <X11/cursorfont.h>
#include <stdlib.h>
#include "util.h"
#include "polywm.h"
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include "config.h"

char buf[64];

int width, height;
int current_workspace = 0;
Window windows[WORKSPACES][2] = { { 0 } };
int win_count[WORKSPACES] = { 0 };

Display *dis;
Window root;
XEvent ev;
GC gc;
XColor xcolor;
int screen_number;


int main()
{

    if(!(dis = XOpenDisplay(NULL))) return 1;
    screen_number = DefaultScreen(dis);
    root = DefaultRootWindow(dis);

    for(int i = 0; i<LENGTH(keys); i++) {
        grab_key(dis, root, keys[i].key, keys[i].mod);
    }

    Cursor cursor = XCreateFontCursor(dis, XC_left_ptr);
    XDefineCursor(dis, root, cursor);


    Colormap colormap = DefaultColormap(dis, screen_number);

    XAllocNamedColor(dis, colormap, BG_COLOR, &xcolor, &xcolor);
    XSetWindowBackground(dis, root, xcolor.pixel);

    XFontStruct *font = XLoadQueryFont(dis, "fixed");
    gc = XCreateGC(dis, root, 0, NULL);
    XSetFont(dis, gc, font->fid);
    XSetForeground(dis, gc, WhitePixel(dis, screen_number));
    XClearWindow(dis, root);


    width = XDisplayWidth(dis, screen_number);
    height = XDisplayHeight(dis, screen_number);

    XDrawString(dis, root, gc, 0, height-(BAR_HEIGHT/2), buf, strlen(buf));
    XSelectInput(dis, root, SubstructureRedirectMask | SubstructureNotifyMask);

    XSync(dis, False);

    for(;;) {
        XNextEvent(dis, &ev);

        if(ev.type == MapRequest) {
            map_request_handler(dis, &ev);
        }

        else if(ev.type == KeyPress) {
            KeySym ks = XLookupKeysym(&ev.xkey, 0);
            // handles key
            for(int i = 0; i<LENGTH(keys); i++) {
                if(ks == keys[i].key && (ev.xkey.state & keys[i].mod)) {
                    keys[i].handler();
                }
            }
        }

        else if(ev.type == EnterNotify) {
            set_focus(ev.xcrossing.window);
            char *title;
            if(XFetchName(dis, ev.xcrossing.window, &title)) {
                render_text(title);
                XFree(title);
            }
        }

        else if(ev.type == UnmapNotify) {
            if(ev.xunmap.send_event) {
                if(win_count[current_workspace] > 0) {
                    set_focus(windows[current_workspace][0]);
                } else {
                    set_root_focus();
                    break;
                }
                continue;
            }
            for(int i = 0; i < win_count[current_workspace]; i++) {
                if(windows[current_workspace][i] == ev.xunmap.window) {
                    windows[current_workspace][i] = windows[current_workspace][win_count[current_workspace] -1];
                    win_count[current_workspace]--;
                    tile_windows();
                    if(win_count[current_workspace] > 0) {
                        set_focus(windows[current_workspace][0]);
                    } else {
                        set_root_focus();
                        break;
                    }
                }
            }
        }

        else if(ev.type == DestroyNotify) {
            for(int ws = 0; ws < WORKSPACES; ws++) {
                for(int i = 0; i < win_count[ws]; i++) {
                    if(windows[ws][i] == ev.xdestroywindow.window) {
                        windows[ws][i] = windows[ws][win_count[ws] - 1];
                        win_count[ws]--;
                        if(ws == current_workspace) {
                            tile_windows();
                        }
                        break;
                    }
                }
            }
        }
    }
    XFreeCursor(dis, cursor);
    XCloseDisplay(dis);
}
