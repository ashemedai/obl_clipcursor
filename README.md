# Oblivion Inactive Window Scroll Fix 🖱

This is a port of the [Inactive Window Scroll Fix for Fallout 3](https://github.com/dekart811/fo3_clipcursor), made by [dekart811](https://github.com/dekart811).
Which in itself is a port of the [Inactive Window Scroll Fix for Fallout New Vegas](https://github.com/luluco250/fnv_clipcursor), made by [luluco250](https://github.com/luluco250).
All credits go to them.

As xOBSE is compiled with Visual Studio 2019, this project does similarly.

Everything below the line is their original README.md, adjusted for Oblivion and
OBSE.

---

Fixes the problematic behavior of mouse scrolling not being fully captured by
the game, which results in scrolling other applications in other windows due to
Windows 10's inactive window scroll feature.

This is more noticeable with multi-monitor setups, for example, when scrolling
through a menu, you might notice your browser on another screen scrolls as well.

This is because the mouse cursor seems to not actually be restricted to the
window. It's obvious why this was never a problem before Windows 10, but now it
needs fixing. 😉

This uses the `ClipCursor()` function of the Win32 API to restrict the mouse
to the game window's boundaries, only letting go when it loses focus (such as
alt-tabbing).

This has also been tested with ReShade and thus *should* be compatible with
other overlays as well. 🎮

## How to Build

OBSE source code is not provided as per the license agreement, so to build this
plugin you'll need to grab it [here](https://github.com/llde/xOBSE) (download
the latest version).

After that, copy `src/common` and `src/obse` to the folder before where this
project is located (like `src/obse_plugin_example`). It should look like this:

```
📁...
└📁common
└📁obl_clipcursor
 └...
 └📄obl_clipcursor.sln
 └...
└📁obse
```
