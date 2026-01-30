#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include <string.h>

void grab_key(Display *dis, Window root, KeySym key, unsigned int modifier)
{
    unsigned int lock_modifiers[] = { 0, Mod2Mask, LockMask, Mod2Mask | LockMask };

    for (int i = 0; i < 4; i++) {
        XGrabKey(dis, XKeysymToKeycode(dis, key), modifier | lock_modifiers[i], root,
                 True, GrabModeAsync, GrabModeAsync);
    }
}

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

void set_root_focus()
{
    XSetInputFocus(dis, root, RevertToPointerRoot, CurrentTime);
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

    if(focus != root && focus != None && focus != PointerRoot) {
        XKillClient(dis, focus);
    }
}

void load_workspace()
{
    char *title;

    width = DisplayWidth(dis, screen_number);
    height = DisplayHeight(dis, screen_number);

    if(XFetchName(dis, ev.xcrossing.window, &title)) {
        render_text(title);
        XFree(title);
    }
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
            if(XFetchName(dis, windows[current_workspace][1], &title)) {
                render_text(title);
                XFree(title);
            }
        } else {
            XSetInputFocus(dis, windows[current_workspace][0], RevertToPointerRoot, CurrentTime);
            char *title;
            if(XFetchName(dis, windows[current_workspace][0], &title)) {
                render_text(title);
                XFree(title);
            }
        }
    }
}


void map_request_handler(Display *dis, XEvent *ev)
{
    Window transient_for;
    if(XGetTransientForHint(dis, ev->xmaprequest.window, &transient_for)) {
        XMapWindow(dis, ev->xmaprequest.window);
        XSetInputFocus(dis, ev->xmaprequest.window, RevertToPointerRoot, CurrentTime);
        return;
    }


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


void set_focus(Window window)
{
    if(window == None || window == root) {
        set_root_focus();
        return;
    }

    XWindowAttributes attr;

    if(XGetWindowAttributes(dis, window, &attr) && attr.map_state == IsViewable) {
        XSetInputFocus(dis, window, RevertToPointerRoot, CurrentTime);
    } else {
        set_root_focus();
    }
}

