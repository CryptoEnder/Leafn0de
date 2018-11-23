
Debian
====================
This directory contains files used to package leafn0ded/leafn0de-qt
for Debian-based Linux systems. If you compile leafn0ded/leafn0de-qt yourself, there are some useful files here.

## leafn0de: URI support ##


leafn0de-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install leafn0de-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your leafn0deqt binary to `/usr/bin`
and the `../../share/pixmaps/leafn0de128.png` to `/usr/share/pixmaps`

leafn0de-qt.protocol (KDE)

