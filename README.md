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


![Screenshot From 2025-04-10 12-28-28](https://github.com/user-attachments/assets/4b4089c6-540e-47aa-981a-68c6040429fb)
![Screenshot From 2025-04-10 12-28-14](https://github.com/user-attachments/assets/c3d24303-d9b6-4953-961d-afba28060125)
![Screenshot From 2025-04-10 12-28-01](https://github.com/user-attachments/assets/894180bd-f5a3-48b0-8f15-12dddf9d3be2)
![Screenshot From 2025-04-10 12-27-53](https://github.com/user-attachments/assets/0d0980f0-740c-47ac-a4f1-ec4fff3bec1a)
![Screenshot From 2025-04-10 12-27-43](https://github.com/user-attachments/assets/a27374dc-33e7-4233-b900-095852cef11c)
