#include <X11/Xlib.h>

void grab_key(Display *dis, Window root, KeySym key, unsigned int modifier)
{
    unsigned int lock_modifiers[] = { 0, Mod2Mask, LockMask, Mod2Mask | LockMask };

    for (int i = 0; i < 4; i++) {
        XGrabKey(dis, XKeysymToKeycode(dis, key), modifier | lock_modifiers[i], root,
                 True, GrabModeAsync, GrabModeAsync);
    }
}
