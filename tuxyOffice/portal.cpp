// tuxyOffice/portal.cpp/
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
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

Fl_Window *prtlwin = new Fl_Window(1024,512,"Tuxy Office portal");
Fl_Window *tskman = new Fl_Window(1024,718,"Task Manager");
Fl_Window *tskopt = new Fl_Window(512, 718,"Task Manager Options");
Fl_Window *tdtwin = new Fl_Window(1024,718,"T-Edit");

Fl_Text_Buffer *tdtbuf = new Fl_Text_Buffer();
Fl_Text_Editor *tdtedt = new Fl_Text_Editor(0, 25, 1024, 670);

int nodex = 0;
int nodey = 0;

void tedit(Fl_Widget *widget, void*) {
	tdtwin->end();
	tdtwin->show();
}

void taskman(Fl_Widget *widget, void*) {
	tskman->end();
	tskman->show();
	tskopt->end();
	tskopt->show();
}

void on_portal_close(Fl_Widget *widget, void*) {
	exit(0);
}

void tdtclose(Fl_Widget *widget, void*) {
	tdtwin->hide();
}

void tdtopen(Fl_Widget *widget, void*) {
	tdtedt->buffer(tdtbuf);
	Fl_File_Chooser fc(".", "*", Fl_File_Chooser::SINGLE, "Open");
	fc.show(); while (fc.shown()) Fl::wait();  
	if (!fc.value()) return;  

	std::ifstream file(fc.value());  
	tdtbuf->text(std::string((std::istreambuf_iterator<char>(file)), {}).c_str());
}

void tdtsave(Fl_Widget* widget, void* data) {
	tdtedt->buffer(tdtbuf);
	const char* result = fl_input("File name:", "noname.txt");

	if (result != NULL) {
		ofstream file(result);

		file << tdtbuf->text();

		file.close();
	} else {
		fl_alert("ERROR, was the filename input null?");
    }
}

void on_tskman_close(Fl_Widget *widget, void*) {
	tskman->hide();
	tskopt->hide();
}

void new_node(Fl_Widget *widget, void*) {
	tskman->begin();

	Fl_Box *box = new Fl_Box(100, 100, 100, 100, "Node");

	box->box(FL_UP_BOX);

	cout << "new node";
}

int main() {
	tskman->end();
	tskopt->end();
	prtlwin->begin();

	Fl_Button *tdtbtn = new Fl_Button(0, 364, 75, 25, "T-Edit");
	Fl_Button *tskbtn = new Fl_Button(80, 364, 105, 25, "T-ask Manager");

	tdtbtn->callback(tedit);
	tskbtn->callback(taskman);

	prtlwin->end();
	prtlwin->show();

	tskman->begin();
	tskman->end();

	tskopt->begin();

	char nodexstr = u_char(nodex);
	char nodeystr = u_char(nodey);

	Fl_Button *tskmovup = new Fl_Button(86, 25, 25, 25, "/\\");
	Fl_Button *tskmovleft = new Fl_Button(25, 50, 25, 25, "<");
	Fl_Button *tskmovright = new Fl_Button(150, 50, 25, 25, ">");
	Fl_Button *tskmovdown = new Fl_Button(86, 75, 25, 25, "\\/");

	Fl_Button *nwndbtn = new Fl_Button(5, 100, 75, 25, "new");

	nwndbtn->callback(new_node);

	tskopt->end();

	prtlwin->callback(on_portal_close);

	tdtwin->begin();

	tdtedt->buffer(tdtbuf);

	char search[256];
	
	int changed = 0;
	char filename[256] = "";

	Fl_Button *tdtsve = new Fl_Button(0, 0, 75, 25, "Save");
	Fl_Button *tdtopn = new Fl_Button(80, 0, 75, 25, "Open");
	Fl_Button *tdtext = new Fl_Button(160, 0, 75, 25, "Exit");

	tdtext->callback(tdtclose);

	tdtopn->callback(tdtopen);
	tdtsve->callback(tdtsave);

	tdtwin->end();

	tskman->callback(on_tskman_close);
	tskopt->callback(on_tskman_close);

	return Fl::run();
}
