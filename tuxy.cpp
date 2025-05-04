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
#include <FL/Fl_Choice.H>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "lib/jokes.h" // Include jokes for the joke button
#include "lib/init.h"  // Include initialization for the style

using namespace std;

// Flag to check if hello message is shown
bool hello = false;

string var1sysinfo;
string strStyle;

// Loading PNG images (assistant image and settings icon)
Fl_PNG_Image *assistant = new Fl_PNG_Image("assistants/orby/orby.png");
Fl_PNG_Image *settingsIcon = new Fl_PNG_Image("assets/icons/Settings.png");

// Window and widget declarations
Fl_Window *imgwin;
Fl_Window *optwin;
Fl_Window *setwin;

Fl_Box *box;

Fl_Button *setbtn;

Fl_Choice *style;

// Joke callback function to display random joke from the jokes library
void joke(Fl_Widget *widget, void*) {
	// Display a random joke using an alert dialog
	fl_alert(Jokes[rand() % (sizeof(Jokes) / sizeof(Jokes[0]))].c_str());
}

// System info callback function to fetch and display system information
void sysinfo(Fl_Widget *widget, void*) {
	// Run a Python script to gather system info
	system("python3 getsysinfo.py");
	ifstream file("sysinfo.txt");
	string f;
	string f2;
	// Read system info from file
	while (getline(file, f)) {
		f2.append(f);
	}
	// Show the system info in a popup dialog
	fl_alert(f2.c_str());
}

// Callback function to open the Tuxy Office portal
void office(Fl_Widget *widget, void*) {
	// Execute the tuxyOffice/portal executable
	system("./tuxyOffice/portal");
}

// Window close callback function to exit the program
void on_window_close(Fl_Widget *widget, void*) {
	exit(0);
}

// Change assistant image to tux (callback for "1" button)
void assist1(Fl_Widget *widget, void*) {
	delete assistant;
	// Load new image for the assistant (Tux)
	assistant = new Fl_PNG_Image("assistants/tux/tux.png");

	// Register images with FLTK
	fl_register_images();

	// Check if the image failed to load
	if (assistant->fail()) {
		fl_alert("Failed to load image");
	} else {
		// Update the window with the new image
		optwin->begin();
		box->image(assistant);
		imgwin->label("Tux");
		optwin->redraw();
		imgwin->redraw();
	}
}

// Change assistant image to Orby (callback for "2" button)
void assist2(Fl_Widget *widget, void*) {
	delete assistant;
	// Load Orby image for the assistant
	assistant = new Fl_PNG_Image("assistants/orby/orby.png");

	// Register images with FLTK
	fl_register_images();

	// Check if the image failed to load
	if (assistant->fail()) {
		fl_alert("Failed to load image");
	} else {
		// Update the window with the new image
		optwin->begin();
		box->image(assistant);
		imgwin->label("Orby");
		imgwin->redraw();
	}
}

// Callback function to show the settings window
void settings(Fl_Widget *widget, void*) {
	setwin->show();
}

// Callback function to change the style of the application (based on the user's selection)
void changeStyle(Fl_Widget *widget, void*) {
	int i;

	i = style->value(); // Get the selected style index

	switch(i) {
		case 0:
			Fl::scheme("classic"); // Apply classic theme
			init::loadStyle(i);    // Load the style
			break;
		case 1:
			Fl::scheme("gleam");   // Apply gleam theme
			init::loadStyle(i);    // Load the style
			break;
		case 2:
			Fl::scheme("gtk+");    // Apply GTK+ theme
			init::loadStyle(i);    // Load the style
			break;
	}
}

int main() {
    fl_register_images(); // Initialize image library

    // Create the main window for the assistant image
    imgwin = new Fl_Window(assistant->w(), assistant->h(), "Orby");

    // Check if the image failed to load and exit if so
    if (assistant->fail()) {
        fl_alert("Failed to load image");
        return 1;
    }

    // Create a box to contain the assistant image
    box = new Fl_Box(0, 0, assistant->w(), assistant->h());
    box->image(assistant); // Display the assistant image in the box

    // Create the options window (window with all of the buttons and options)
    optwin = new Fl_Window(500, 250, "Option");

    imgwin->end();   // End the main window definition
    optwin->begin(); // Start the options window definition

    // Set the callbacks for closing the windows
    optwin->callback(on_window_close);
    imgwin->callback(on_window_close);

    // Create buttons for jokes, system info, and Tuxy Office
    Fl_Button *jkebtn = new Fl_Button(0, 0, 75, 25, "Joke");
    Fl_Button *sysbtn = new Fl_Button(90, 0, 75, 25, "sys info");
    Fl_Button *ofcbtn = new Fl_Button(180, 0, 80, 25, "Tuxy Office");
    
    // Attribution box at the bottom
    Fl_Box *attribution = new Fl_Box(200, 225, 75, 25, "*Image made by Larry Ewing at lewing@@isc.tamu.edu with the GIMP");

    // Number buttons for changing assistant images
    Fl_Button *onebtn = new Fl_Button(5, 150, 25, 25, "1");
    Fl_Button *twobtn = new Fl_Button(35, 150, 25, 25, "2");

    // Settings button
    Fl_Button *setbtn2 = new Fl_Button(470, 5, 25, 25, "@menu");
    setbtn2->labelcolor(FL_GRAY);

    // Set button callbacks
    jkebtn->callback(joke);
    sysbtn->callback(sysinfo);
    ofcbtn->callback(office);

    // Set assistant change callbacks
    onebtn->callback(assist1);
    twobtn->callback(assist2);
    setbtn2->callback(settings);

    // Settings window definition
    setwin = new Fl_Window(512, 256, "Settings");

    optwin->end();    // End the options window definition
    setwin->begin();  // Start the settings window definition

    // Create a choice box for selecting the style
    style = new Fl_Choice(100, 80, 100, 25);
    style->add("Classic");
    style->add("Gleam");
    style->add("GTK+");
    style->value(0); // Default selected style is "Classic"
    style->callback(changeStyle);

    // Show the option and image windows
    optwin->show();
    imgwin->show();

    return(Fl::run()); // Start the FLTK event loop
}

