#!/bin/bash
# install.sh

INSTALL_DIR="build" # the installation folder
SOURCE_FILE="tuxy.cpp" # the source file to compile
OUTPUT_BINARY="tuxy" # the name of the compiled binary


if ! command -v g++ &> /dev/null; then
    echo "Error: g++ is not installed. Install it and try again."
    exit 1
fi

echo "Compiling $SOURCE_FILE..."

g++ $SOURCE_FILE -o $OUTPUT_BINARY -lfltk -lfltk_images -lX11 -lXext -lpthread -lm # the compile command

if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

echo "Changing Permissions..."
chmod +x "$OUTPUT_BINARY" # making the compiled binary able to run

echo "Generating user data..."
read -p "Yes or No?: " input

if ["$input = y"]; then
	python3 getsysinfo.py
elif ["$input = n"]; then
	echo "Will not generate user data..."
else
	echo "Invalid user input. Exiting..."
	exit 1
fi

echo "Installation complete..."
