
Debian
====================
This directory contains files used to package cuckoocoind/cuckoocoin-qt
for Debian-based Linux systems. If you compile cuckoocoind/cuckoocoin-qt yourself, there are some useful files here.

## cuckoocoin: URI support ##


cuckoocoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install cuckoocoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your cuckoocoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/cuckoocoin128.png` to `/usr/share/pixmaps`

cuckoocoin-qt.protocol (KDE)

