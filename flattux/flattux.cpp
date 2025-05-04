// flattux.cpp

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

// Main window pointer declaration
Fl_Window *mainwin;

int main() {
    // Create a new FLTK window with the size 1024x718 and title "Flattux - Flatpak manager"
    mainwin = new Fl_Window(1024, 718, "Flattux - Flatpak manager");

    // Create a new FLTK box (text label) at position (512, 359) with size 100x75
    // and the text "This feature is not finished"
    Fl_Box *box = new Fl_Box(512, 359, 100, 75, "This feature is not finished");

    // Finalize the window setup (add all widgets, close the window setup)
    mainwin->end();

    // Show the main window
    mainwin->show();

    // Start the FLTK event loop (this keeps the window open and interactive)
    return(Fl::run());
}

