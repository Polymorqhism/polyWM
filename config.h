#include <X11/keysym.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "util.h"

#define BG_COLOR "#090017"


void spawn_terminal();
void quit();
void dmenu();

static Keybind keys[] = {
    { XK_Return, Mod4Mask, spawn_terminal },
    { XK_d, Mod4Mask, dmenu },
    { XK_p, Mod4Mask, quit },
};
