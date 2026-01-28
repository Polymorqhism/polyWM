#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "config.h"


Window windows[2];
int win_count = 0;

Display *dis;
Window root;
XEvent ev;


void spawn_terminal() { system("alacritty &"); }
void quit() { system("killall Xorg"); }
void dmenu() { system("dmenu_run &"); }

void close()
{
    Window focus;
    int revert;

    XGetInputFocus(dis, &focus, &revert);

    if(focus != root && focus != None) {
        XKillClient(dis, focus);
    }
}

void tile_windows(Display *dis, int screen_number)
{
    /*
       yes, i am getting dimensions every time i have to re-tile windows
       call it bad practice, i call it 'safety' if the dimensions SOMEHOW change before re-tiling
     */

    int width, height;

    width = XDisplayWidth(dis, screen_number);
    height = XDisplayHeight(dis, screen_number);

    if(win_count == 1) {
        XMoveResizeWindow(dis, windows[0], 0, 0, width, height-5);
    } else if(win_count == 2) {
        XMoveResizeWindow(dis, windows[0], 0, 0, width/2, height-5);
        XMoveResizeWindow(dis, windows[1], width/2, 0, width/2, height-5);
    }
}

void map_request_handler(Display *dis, XEvent *ev, int screen_number)
{
    if((win_count < 3)) {
        windows[win_count] = ev->xmaprequest.window;
        win_count++;
    }

    XSelectInput(dis, ev->xmaprequest.window, EnterWindowMask);
    XMapWindow(dis, ev->xmaprequest.window);
    XAddToSaveSet(dis, ev->xmaprequest.window);
    XSetInputFocus(dis, ev->xmaprequest.window, RevertToPointerRoot, CurrentTime);
    tile_windows(dis, screen_number);
}

int main()
{

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
            map_request_handler(dis, &ev, screen_number);
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
            XSetInputFocus(dis, ev.xcrossing.window, RevertToPointerRoot, CurrentTime);
        }

        else if(ev.type == DestroyNotify) {
            for(int i = 0; i < win_count; i++) {
                if(windows[i] == ev.xdestroywindow.window) {
                    windows[i] = windows[win_count -1];
                    win_count--;
                    tile_windows(dis, screen_number);
                    if(win_count > 0) {
                        XSetInputFocus(dis, windows[0], RevertToPointerRoot, CurrentTime);
                    }
                    break;
                }
            }
        }
    }

    XFreeCursor(dis, cursor);
    XCloseDisplay(dis);
    return 0;
}
