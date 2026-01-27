#include <X11/keysym.h>
#include <X11/Xlib.h>
#include "polywm.h"

#define BG_COLOR "#090017"


void spawn_terminal();
void quit();

typedef struct {
    KeySym key;
    unsigned int mod;
    void (*handler)(void);
} Keybind;

static Keybind keys[] = {
    { XK_Return, Mod4Mask, spawn_terminal },
    { XK_p, Mod4Mask, quit },
};
