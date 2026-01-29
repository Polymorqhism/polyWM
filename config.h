#define BG_COLOR "#293329"
#define BAR_HEIGHT 20
#define WORKSPACES 6

void spawn_terminal();
void quit();
void dmenu();
void close();
void change_focus();
void workspace_front();
void workspace_back();


static Keybind keys[] = {
    { XK_Return, Mod4Mask, spawn_terminal },
    { XK_d, Mod4Mask, dmenu },
    { XK_p, Mod4Mask, quit },
    { XK_q, Mod4Mask, close },
    { XK_f, Mod4Mask, change_focus },
    { XK_j, Mod4Mask, workspace_back },
    { XK_k, Mod4Mask, workspace_front },
};
