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

void initload() {

}

void joke(Fl_Widget *widet, void*) {
	fl_alert(Jokes[rand() % (sizeof(Jokes) / sizeof(Jokes[0]))].c_str());
}

void on_window_close(Fl_Widget *w, void*) {
	exit(0);
}

int main() {
	Fl_PNG_Image *tux = new Fl_PNG_Image("pictures/tuxy.png");

    	fl_register_images();                       // initialize image lib
						    
    	Fl_Window *imgwin = new Fl_Window(tux->w(),tux->h(),"Tuxy");                 // make a window

	if (tux->fail()) {
        	fl_alert("Failed to load image");
        	return 1;
	}

    	Fl_Box *box = new Fl_Box(0, 0, tux->w(), tux->h());     // widget that will contain image
    	box->image(tux);					// attach jpg image to box

	Fl_Window *optwin = new Fl_Window(500, 250, "Option");

	imgwin->end();
	optwin->begin();
    	
	optwin->callback(on_window_close);
	imgwin->callback(on_window_close);

	Fl_Button *btn1 = new Fl_Button(0, 0, 75, 25, "Joke");

	btn1->callback(joke);

	optwin->end();
	optwin->show();
	imgwin->show();

    	return(Fl::run());
}


