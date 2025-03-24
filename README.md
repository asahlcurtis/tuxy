This is a virtual assistant I am making, it's called tuxy. The name is a reference to Clippy.

It isn't finished right now, not even close. But I think it's cool. Right now currently it only tells jokes and shows a really first page of google image of tux.

To build you need fltk and g++. You can type g++ tuxy.cpp -o tuxy -lfltk -lfltk_images -lX11 -lXext -lpthread -lm or type make in the terminal.

you can download the dependencies with your package manager

Fedora:

	g++:
	sudo dnf install gcc-c++

	fltk:
	sudo dnf install fltk

Ubuntu/Debian:
	
	g++:
	sudo apt install g++

	fltk:
	sudo apt install libfltk1.3-dev

Arch
	
	g++:
	sudo pacman -S gcc

	fltk:
	sudo pacman -S fltk

Gentoo:
	
	g++:
	sudo emerge sys-devel/gcc

	fltk:
	sudo emerge x11-libs/fltk

FreeBSD:

	g++:
	sudo pkg install gcc

	fltk:
	sudo pkg install fltk

If I didn't cover you OS. Sorry you better know the library naming rules of your package manager and remember the latest version of fltk!
If your OS is Windows or macOS why are you installing a piece of software which is built around tux?
