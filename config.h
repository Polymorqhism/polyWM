#include <X11/Xlib.h>
#include "binds/binds.h"

static Keybind keys[] = {
    { XK_Return, Mod4Mask, spawn, {.v = "kitty"} },
    { XK_d, Mod4Mask, spawn, {.v = "dmenu_run"} }
};
