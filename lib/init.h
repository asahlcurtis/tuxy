// init.h

#ifndef INIT_H
#define INIT_H

// If you are using a very old compiler that doesn't support #pragma once, 
// you can remove this line.
#pragma once

// Include necessary libraries for file handling and string manipulation
#include <iostream>
#include <fstream>
#include <string>

// Define the 'init' namespace to contain initialization functions
namespace init {

	// Function to initialize the style by writing the style name to a file
	void styleInit(std::string s) {
		// Open a file in write mode, the style information is written here
		std::ofstream stylePipe("tmp/stylePipe");

		// Write the style name to the file
		stylePipe << s;

		// Close the file after writing the style information
		stylePipe.close();
	}

	// Function to load a specific style based on the provided index
	void loadStyle(int i) {
		// Switch statement to select style based on the index
		switch (i) {
			case 0: {
				// If index is 0, load the 'classic' style
				std::string classic = "classic";
				styleInit(classic);
				break;
			}

			case 1: {
				// If index is 1, load the 'gleam' style
				std::string gleam = "gleam";
				styleInit(gleam);
				break;
			}

			case 2: {
				// If index is 2, load the 'gtk+' style
				std::string gtk = "gtk+";
				styleInit(gtk);
				break;
			}
		}
	}

	// Function to quit and clear the style settings by writing an empty string
	void quit() {
		// Open the stylePipe file to clear the style settings
		std::ofstream stylePipe("tmp/stylePipe");

		// Write an empty string to the file, effectively clearing the style
		stylePipe << "";

		// Close the file
		stylePipe.close();
	}
}

#endif

