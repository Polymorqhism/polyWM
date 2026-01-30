#include <X11/Xlib.h>
#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#include <X11/keysym.h>
#include "polywm.h"

void grab_key(Display *dis, Window root, KeySym key, unsigned int modifier);
void render_text(char *title);
void load_workspace();
void workspace_back();
void workspace_front();
void change_focus();
void map_request_handler(Display *dis, XEvent *ev);
void set_focus(Window window);
void unload_workspace();
void tile_windows();
void set_root_focus();
