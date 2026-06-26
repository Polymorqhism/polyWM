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
