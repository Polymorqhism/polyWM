#include "../globals.h"

typedef union {
    int i;
    unsigned int ui;
    float f;
    const void *v;
} Arg;

typedef struct {
    KeySym key;
    unsigned int mod;
    void (*handler)(const Arg *);
    const Arg arg;
} Keybind;

extern void spawn(const Arg *arg);
