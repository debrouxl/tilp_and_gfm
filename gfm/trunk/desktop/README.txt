This directory contains FreeDesktop.org Desktop definitions for GFM.

If your desktop environment doesn't detect the files after `make install`, run:
* `update-desktop-database`;

This also now contains an AppData XML file, that can be validated using the
tool `appstream-util validate [PREFIX]/share/appdata/gfm.appdata.xml`.

See https://secure.freedesktop.org/~hughsient/appdata/ for more on the
specification.

