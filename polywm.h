#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))

typedef struct {
    KeySym key;
    unsigned int mod;
    void (*handler)(void);
} Keybind;
