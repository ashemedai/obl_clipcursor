# Oblivion Inactive Window Scroll Fix 🖱

This is a port of the [Inactive Window Scroll Fix for Fallout 3](https://github.com/dekart811/fo3_clipcursor), made by [dekart811](https://github.com/dekart811).
Which in itself is a port of the [Inactive Window Scroll Fix for Fallout New Vegas](https://github.com/luluco250/fnv_clipcursor), made by [luluco250](https://github.com/luluco250).
All credits for the initial version go to them.

## Requirements

This plugin requires **xOBSE 22.10 or newer**.

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

---

## How to Build

The xOBSE source code isn't bundled with this repository.

Either of these gets you a correctly pinned, correctly named `xOBSE` folder:

- `git clone https://github.com/llde/xOBSE.git`, then `git checkout <tag>`
  (e.g. `git checkout 22.13`) inside the cloned repository.
- Or download the [release's source code archive](https://github.com/llde/xOBSE/releases)
  (either zip or tarball), which extracts to `xOBSE-<version>`. Rename the
  extracted folder to `xOBSE`.

You should have the resulting `xOBSE` folder as a sibling of this project (so
not nested inside it). It should look like this:

```text
📁 ...
└📁 obl_clipcursor
 └ ...
 └📄 obl_clipcursor.sln
 └ ...
└📁 xOBSE
 └📁 common
 └📁 obse
 └ ...
```
