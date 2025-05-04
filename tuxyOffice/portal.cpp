// tuxyOffice/portal.cpp

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Color_Chooser.H>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include "../lib/node.h"

using namespace std;

// Main window for the portal
Fl_Window *prtlwin = new Fl_Window(1024,512,"Tuxy Office portal");

// Task manager window and its options
Fl_Window *tskman = new Fl_Window(1024,718,"Task Manager");
Fl_Window *tskopt = new Fl_Window(512, 718,"Task Manager Options");

// Text editor window
Fl_Window *tdtwin = new Fl_Window(1024,718,"T-Edit");

// Text buffer and editor for the text editor window
Fl_Text_Buffer *tdtbuf = new Fl_Text_Buffer();
Fl_Text_Editor *tdtedt = new Fl_Text_Editor(0, 25, 1024, 670);

// Canvas and node instances for task manager
Canvas* canvas;
Node* exmnod;

// Node color chooser
Fl_Color_Chooser* nodclr;

// Variables for node positioning
int nodex = 0;
int nodey = 0;

// Function to open the text editor window
void tedit(Fl_Widget *widget, void*) {
    tdtwin->end();
    tdtwin->show();
}

// Function to open the task manager window and options
void taskman(Fl_Widget *widget, void*) {
    tskman->end();
    tskman->show();
    tskopt->end();
    tskopt->show();
}

// Function to close the portal window and exit
void on_portal_close(Fl_Widget *widget, void*) {
    exit(0);
}

// Function to close the text editor window
void tdtclose(Fl_Widget *widget, void*) {
    tdtwin->hide();
}

// Function to open a file in the text editor
void tdtopen(Fl_Widget *widget, void*) {
    tdtedt->buffer(tdtbuf);
    Fl_File_Chooser fc(".", "*", Fl_File_Chooser::SINGLE, "Open");
    fc.show(); 
    while (fc.shown()) Fl::wait();  
    if (!fc.value()) return;  // If no file was chosen, return

    // Open and read the selected file into the text buffer
    std::ifstream file(fc.value());  
    tdtbuf->text(std::string((std::istreambuf_iterator<char>(file)), {}).c_str());
}

// Function to save the text from the editor to a file
void tdtsave(Fl_Widget* widget, void* data) {
    tdtedt->buffer(tdtbuf);
    const char* result = fl_input("File name:", "noname.txt");

    if (result != NULL) {
        // Open the file and write the text buffer to it
        ofstream file(result);
        file << tdtbuf->text();
        file.close();
    } else {
        // Alert if the file name was null
        fl_alert("ERROR, was the filename input null?");
    }
}

// Function to close the task manager window and options
void on_tskman_close(Fl_Widget *widget, void*) {
    tskman->hide();
    tskopt->hide();
}

// Function to add a new node to the task manager canvas
void new_node(Fl_Widget *widget, void*) {
    tskman->begin();
    
    // Create a new node and add it to the task manager canvas
    Fl_Box *box = new Fl_Box(100, 100, 100, 100, "Node");
    box->box(FL_UP_BOX);  // Style the box

    cout << "new node";
}

// Function to set the FLTK scheme based on the style file
void setrfs() {
    string style;

    // Open and read the style file
    ifstream styleFile("tmp/stylePipe");

    while (getline (styleFile, style)) {
        const char* stylechar = style.c_str();
        Fl::scheme(stylechar);  // Set the FLTK scheme to the style read from the file
    }
}

// Function to update the node color based on the color chooser
void clrcb(Fl_Widget *widget, void*) {
    double r = nodclr->r();
    double g = nodclr->g();
    double b = nodclr->b();

    Fl_Color color = fl_rgb_color((uchar)(r * 255), (uchar)(g * 255), (uchar)(b * 255));
    exmnod->color(color);  // Set the color of the node
    exmnod->redraw();  // Redraw the node with the new color
}

int main() {
    setrfs();  // Set the FLTK scheme based on the style

    // End the windows setup
    tskman->end();
    tskopt->end();
    prtlwin->begin();

    // Create and add buttons for opening the text editor and task manager
    Fl_Button *tdtbtn = new Fl_Button(0, 364, 75, 25, "T-Edit");
    Fl_Button *tskbtn = new Fl_Button(80, 364, 105, 25, "T-ask Manager");

    tdtbtn->callback(tedit);  // Button callback for text editor
    tskbtn->callback(taskman);  // Button callback for task manager

    prtlwin->end();
    prtlwin->show();  // Show the main window

    // Setup the task manager window
    tskman->begin();

    canvas = new Canvas(0, 0, 1024, 718);  // Create a canvas for the task manager
    exmnod = new Node(100, 200, 100, 50, "Example Node");  // Create an example node

    tskman->end();  // End task manager setup

    // Setup the task options window
    tskopt->begin();

    nodclr = new Fl_Color_Chooser(15, 15, 300, 100, "Node Color");  // Create a color chooser for node color

    Fl_Button* clrrfs = new Fl_Button(400, 15, 100, 25, "Refresh");
    Fl_Button* addnod = new Fl_Button(400, 50, 100, 25, "Add Node");

    clrrfs->callback(clrcb);  // Callback for refreshing node color

    exmnod->color(nodclr->value());  // Set the initial color of the example node to the color chooser value

    tskopt->end();  // End task options setup

    prtlwin->callback(on_portal_close);  // Set the close callback for the portal window

    // Setup the text editor window
    tdtwin->begin();

    tdtedt->buffer(tdtbuf);  // Set the buffer for the text editor

    // Create buttons for saving, opening, and exiting the text editor
    Fl_Button *tdtsve = new Fl_Button(0, 0, 75, 25, "Save");
    Fl_Button *tdtopn = new Fl_Button(80, 0, 75, 25, "Open");
    Fl_Button *tdtext = new Fl_Button(160, 0, 75, 25, "Exit");

    tdtext->callback(tdtclose);  // Exit callback for the text editor
    tdtopn->callback(tdtopen);  // Open callback for the text editor
    tdtsve->callback(tdtsave);  // Save callback for the text editor

    tdtwin->end();  // End text editor setup

    // Set close callbacks for task manager and options windows
    tskman->callback(on_tskman_close);
    tskopt->callback(on_tskman_close);

    return Fl::run();  // Run the FLTK event loop
}

