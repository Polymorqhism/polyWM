#include <unistd.h>
#include <stdlib.h>
#include "binds.h"

void spawn(const Arg *arg)
{
    if(fork() == 0) {
        setsid();
        execlp((char *)arg->v, (char *)arg->v, NULL);
        exit(1);
    }
}



void grab_key(Display *dis, Window root, KeySym key, unsigned int modifier)
{
    unsigned int lock_modifiers[] = { 0, Mod2Mask, LockMask, Mod2Mask | LockMask };

    for (int i = 0; i < 4; i++) {
        XGrabKey(dis, XKeysymToKeycode(dis, key), modifier | lock_modifiers[i], root,
                 True, GrabModeAsync, GrabModeAsync);
    }
};
