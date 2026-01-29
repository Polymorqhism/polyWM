#include <X11/Xlib.h>
#include <string.h>
#include <stdio.h>
#include <X11/cursorfont.h>
#include <stdlib.h>
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


void spawn_terminal() { system("alacritty &"); }
void quit() { system("killall Xorg"); }
void dmenu() { system("dmenu_run &"); }

void tile_windows()
{
    if(win_count[current_workspace] == 1) {
        XMoveResizeWindow(dis, windows[current_workspace][0], 0, 0, width, height-BAR_HEIGHT);
    } else if(win_count[current_workspace] == 2) {
        XMoveResizeWindow(dis, windows[current_workspace][0], 0, 0, width/2, height-BAR_HEIGHT);
        XMoveResizeWindow(dis, windows[current_workspace][1], width/2, 0, width/2, height-BAR_HEIGHT);
    }
}

void render_text(char *title)
{
    snprintf(buf, sizeof(buf), "Workspace: %d/%d : %s", current_workspace + 1, WORKSPACES, title);

    XSetForeground(dis, gc, xcolor.pixel);
    XFillRectangle(dis, root, gc, 0, height - BAR_HEIGHT, width, BAR_HEIGHT);

    XSetForeground(dis, gc, WhitePixel(dis, screen_number));
    XDrawString(dis, root, gc, 5, height - (BAR_HEIGHT/2), buf, strlen(buf));
}

void close()
{
    Window focus;
    int revert;

    XGetInputFocus(dis, &focus, &revert);

    if(focus != root && focus != None) {
        XKillClient(dis, focus);
    }
}

void load_workspace()
{
    char *title;

    width = DisplayWidth(dis, screen_number);
    height = DisplayHeight(dis, screen_number);

    XFetchName(dis, ev.xcrossing.window, &title);
    render_text(title);
    for(int i = 0; i<win_count[current_workspace]; i++) {
        XMapWindow(dis, windows[current_workspace][i]);
    }
    tile_windows();
}

void unload_workspace()
{
    for(int i = 0; i<win_count[current_workspace]; i++) {
        XUnmapWindow(dis, windows[current_workspace][i]);
    }
}

void workspace_back()
{
    if (current_workspace > 0) {
        unload_workspace();
        current_workspace--;
        load_workspace();
    }
}

void workspace_front()
{
    if (current_workspace < WORKSPACES - 1) {
        unload_workspace();
        current_workspace++;
        load_workspace();
    }
}

void change_focus()
{
    Window focus;
    int revert;
    XGetInputFocus(dis, &focus, &revert);


    if(focus != root && focus != None && win_count[current_workspace] > 1) {
        if(focus == windows[current_workspace][0]) {
            XSetInputFocus(dis, windows[current_workspace][1], RevertToPointerRoot, CurrentTime);
            char *title;
            XFetchName(dis, windows[current_workspace][1], &title);
            render_text(title);
        } else {
            XSetInputFocus(dis, windows[current_workspace][0], RevertToPointerRoot, CurrentTime);
            char *title;
            XFetchName(dis, windows[current_workspace][0], &title);
            render_text(title);
        }
    }
}


void map_request_handler(Display *dis, XEvent *ev, int screen_number)
{
    if((win_count[current_workspace] < 3)) {
        windows[current_workspace][win_count[current_workspace]] = ev->xmaprequest.window;
        win_count[current_workspace]++;
    }

    XSelectInput(dis, ev->xmaprequest.window, EnterWindowMask);
    XMapWindow(dis, ev->xmaprequest.window);
    XAddToSaveSet(dis, ev->xmaprequest.window);
    XSetInputFocus(dis, ev->xmaprequest.window, RevertToPointerRoot, CurrentTime);
    tile_windows();
}



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
            char *title;
            XFetchName(dis, ev.xcrossing.window, &title);
            render_text(title);
        }

        else if(ev.type == DestroyNotify) {
            for(int i = 0; i < win_count[current_workspace]; i++) {
                if(windows[current_workspace][i] == ev.xdestroywindow.window) {
                    windows[current_workspace][i] = windows[current_workspace][win_count[current_workspace] -1];
                    win_count[current_workspace]--;
                    tile_windows();
                    if(win_count > 0) {
                        XSetInputFocus(dis, windows[current_workspace][0], RevertToPointerRoot, CurrentTime);
                    }
                    break;
                }
            }
        }

        else if(ev.type == UnmapNotify) {
            for(int i = 0; i < win_count[current_workspace]; i++) {
                if(windows[current_workspace][i] == ev.xunmap.window) {
                    windows[current_workspace][i] = windows[current_workspace][win_count[current_workspace] -1];
                    win_count[current_workspace]--;
                    tile_windows();
                    if(win_count[current_workspace] > 0) {
                        XSetInputFocus(dis, windows[current_workspace][0], RevertToPointerRoot, CurrentTime);
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
