<p align="center">
  <img
    src="polyWM.png"
    alt="polyWM"
    width="120"
  />

</p>

<h1 align="center">polyWM</h1>

<p align="center">
  Performance; minimalism.
</p>

> [!TIP]
> This WM focuses on performance and minimalism for low-level developers. It is intended to be used by users who are able to debug issues on their own. It is intentionally stripped down to work on low-end systems.

> [!CAUTION]
> Due to the nature of X11, compiling versions from unknown sources (i.e. not from GitHub) may result in serious system compromise.

---
### More Info

- To prevent clutter and general misuse, polyWM intentionally only allows for two tiles per workspace. If violated, the new window gets pushed out and spawns at the top left of the screen. It will re-tile whenever possible.
- The whole WM is considered experimental. Use at your own risk.
- Uses `dmenu` by default. Change it through `polywm.c` if desired.
- Uses `alacritty` by default. Change it through `polywm.c`.
- Changes will only take effect after the WM is recompiled.
- Do not "rice" this WM. It is intended to be minimal. Any additions come at the cost of possible instability and performance cost.
- polyWM is not responsible for issues caused by modified builds, untested distributions, software or hardware. 

### License
- Uses the GPL-2.0 License. See LICENSE for details.
- polyWM comes with no warranty.

### Get Started

- Compile polyWM by using the Makefile.
- Run `startx` after setting up `.xinitrc` including the executable binary from your TTY.
- Works best on Arch Linux. Other distributions have not been tested.
- Hold `Mod4` (Windows key) and:
  - `ENTER` - opens the terminal (alacritty)
  - `P` - exits polyWM; you can remove this if you wish
  - `Q` - kills a window
  - `D` - dmenu
  - `J/K` - backward/forward workspace movement
  - more keybinds can be found in your `config.h`.
- No installation script is provided. Manage the X startup yourself.


### Prerequisites
- dmenu
- X11
- Alacritty

### About This Project
- The following features (but not limited to) will _**never**_ be added:
  - dynamic layouts
  - animations or effects
  - native ricing support targeting eyecandy
  - Wayland support
- There is no guarantee polyWM works with multi-monitors.
- Tested only on x86_64 CPU architecture.

### FAQ
> **Q:** How do I rice polyWM to look good?
- **A:** You don't.

> **Q:** Why does polyWM only have 2 tiles per workspace?
- **A:** The usage of polyWM is intended to be useful, not overly complicated. Adding support for more than two tiles would mean complicated tiling systems - this comes at the cost of performance, even if little.

> **Q:** What do I do if polyWM crashes and doesn't work?
- **A:** Ensure that your system supports it. Debugging is entirely in the hands of the user. If the issue is reproducible on an unmodified build, open an issue.

> **Q:** How do I change or add more binds?
- **A:** Changing the binds can be done through the file `config.h`. Adding more binds would mean writing their functionality directly.

---

If you are new to Linux, setting up DEs and/or following documentation, do **_not_** use this WM. If you do not understand the contents of this README, you are advised not to use this project.
