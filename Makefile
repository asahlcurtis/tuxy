# Default target to build all the executables
all: tuxy tuxyOffice/portal flattux/flattux

# Rule to build the tuxy executable from tuxy.cpp
tuxy: tuxy.cpp
	# Compile tuxy.cpp using g++ and link with FLTK libraries
	g++ tuxy.cpp -o tuxy -lfltk -lfltk_images
	
# Rule to build the tuxyOffice/portal executable from tuxyOffice/portal.cpp
tuxyOffice/portal: tuxyOffice/portal.cpp
	# Compile tuxyOffice/portal.cpp and link with FLTK libraries
	g++ tuxyOffice/portal.cpp -o tuxyOffice/portal -lfltk -lfltk
	
# Rule to build the flattux/flattux executable from flattux/flattux.cpp
flattux/flattux: flattux/flattux.cpp
	# Compile flattux/flattux.cpp and link with FLTK libraries
	g++ flattux/flattux.cpp -o flattux/flattux -lfltk

# Clean rule to remove the generated executables
clean:
	# Remove the compiled executables to start fresh
	rm -f tuxy tuxyOffice/portal flattux/flattux

# Mark 'all' and 'clean' as phony targets (i.e., not associated with files)
.PHONY: all clean
