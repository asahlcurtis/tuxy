// tuxy.cpp
// tnoremap <Esc> <C-\><C-n> I use nvim btw
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "lib/jokes.h"

using namespace std;

bool hello = false;

string var1sysinfo;

// joke callback for the jokes :D
void joke(Fl_Widget *widet, void*) {
	// the fl_alert dialog
	fl_alert(Jokes[rand() % (sizeof(Jokes) / sizeof(Jokes[0]))].c_str());
}

// callback for generating/opening the system info text file
void sysinfo(Fl_Widget *widget, void*) {
	// running the python file to get the system info
	system("python3 getsysinfo.py");
	ifstream file("sysinfo.txt");
	string f;
	string f2;
	while (getline (file, f)) {
		f2.append(f);
	}
	fl_alert(f2.c_str());
}

void office(Fl_Widget *widget, void*) {
	system("./tuxyOffice/portal");
}

// the window closing callback
void on_window_close(Fl_Widget *w, void*) {
	exit(0);
}

int main() {
	// loading the png image
	Fl_PNG_Image *tux = new Fl_PNG_Image("pictures/tux.png");

    	fl_register_images();                       // initialize image lib

    	Fl_Window *imgwin = new Fl_Window(tux->w(),tux->h(),"Tuxy");                 // make a window

	// just if by some weird thing happened like a cosmic ray hitting a binary bit in my motherboard or disk that deletes the image and then doesn't get to the repo
	if (tux->fail()) {
        	fl_alert("Failed to load image");
        	return 1;
	}

    	Fl_Box *box = new Fl_Box(0, 0, tux->w(), tux->h());     // widget that will contain image
    	box->image(tux);					// the jpg image on box

	// the option window for the program ( the window with all of the function )
	Fl_Window *optwin = new Fl_Window(500, 250, "Option");

	imgwin->end();
	optwin->begin();
    	
	// the callbacks for the windows being closed
	optwin->callback(on_window_close);
	imgwin->callback(on_window_close);

	// the button for the jokes
	Fl_Button *jkebtn = new Fl_Button(0, 0, 75, 25, "Joke");
	Fl_Button *sysbtn = new Fl_Button(90, 0, 75, 25, "sys info");
	Fl_Button *ofcbtn = new Fl_Button(180, 0, 80, 25, "Tuxy Office");

	Fl_Box *attribution = new Fl_Box(200, 225, 75, 25, "*Image made by Larry Ewing at lewing@@isc.tamu.edu with the GIMP");

	// the callbackes for the buttons
	jkebtn->callback(joke);
	sysbtn->callback(sysinfo);
	ofcbtn->callback(office);

	optwin->end();
	optwin->show();
	imgwin->show();

    	return(Fl::run());
}
