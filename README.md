<p align="center">
  <img
    src="https://github.com/user-attachments/assets/cf0ec1b8-dfe5-48c7-89d3-444e847806f9"
    alt="polyWM"
    width="120"
  />
</p>

<h1 align="center">polyWM</h1>

<p align="center">
  Performance; minimalism.
</p>

> [!TIP]
> This WM focuses on performance and minimalism. It is intended to be used by users who are able to debug issues on their own. It is intentionally stripped down to work on low end systems.

> [!CAUTION]
> Due to the nature of X11, compiling versions from unknown sources (i.e. not from GitHub) may result in serious system compromise.

---
### More Info

- To prevent clutter and general misuse, polyWM intentionally only allows for two tiles per workspace.
- The whole WM is considered experimental. Use at your own risk.
- Uses `dmenu` by default. Change it through `polywm.c` if desired.
- Uses `alacritty` by default. Change it through `polywm.c`.
- Changes will only take effect after the WM is recompiled.


### Get Started

- Compile polyWM by using the Makefile
- Run `startx` after setting up `.xinitrc` including the executable binary from your TTY.
- Works best on Arch Linux. Other distributions have not been tested.


### Prerequisites
- dmenu
- X11
- Alacritty

---

If you are new to Linux, setting up DEs and/or following documentation, do **_not_** use this WM.
