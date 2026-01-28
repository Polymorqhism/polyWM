#include <X11/keysym.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "util.h"

#define BG_COLOR "#293329"


void spawn_terminal();
void quit();
void dmenu();
void close();

static Keybind keys[] = {
    { XK_Return, Mod4Mask, spawn_terminal },
    { XK_d, Mod4Mask, dmenu },
    { XK_p, Mod4Mask, quit },
    { XK_q, Mod4Mask, close },
};
