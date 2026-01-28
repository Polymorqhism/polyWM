<p align="center">
  <img
    src="https://github.com/user-attachments/assets/fa87f70b-333b-4aac-8759-00fc5129d530"
    alt="polyWM"
    width="120"
  />
</p>

<h1 align="center">polyWM</h1>

<p align="center">
  Performance; minimalism.
</p>

> [!TIP]
> This WM focuses on performance and minimalism. It is intended to be used by users who are able to debug issues on their own. It is intentionally stripped down.
> This WM works best on low end systems.

> [!CAUTION]
> Due to the nature of X11, compiling versions from unknown sources (i.e. not from GitHub) may result in serious system compromise.

---
### More Info

- _To prevent clutter, polyWM intentionally only allows for two tiles per workspace._
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
