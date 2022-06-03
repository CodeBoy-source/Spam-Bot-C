main: test.c
	gcc  -o main test.c -lX11 -lxcb -lxcb-xtest -lX11-xcb -L /usr/X11R6/lib -lX11 -lXtst -lm

.PHONY: install
install:
	sudo apt-get install xcb libxcb-xkb-dev x11-xkb-utils libx11-xcb-dev libxkbcommon-x11-dev apt-file libxcb-util0-dev libxcb-keysyms1-dev libxcb-xtest0-dev libxtst-dev
