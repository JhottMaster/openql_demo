# Cross-platform compilation:
CC=g++
BASE_LINKED_LIBRARIES=-lGLEW -lglfw -lSOIL
OSX_LINKED_LIBRARIES=-framework OpenGL -framework CoreFoundation
UNIX_LINKED_LIBRARIES=-Wall -lGL

# Build configuration:
EXECUTABLE_NAME=open_gl_demo
BUILD_DIRECTORY=build/bin/
OUTPUT_DIRECTORY=build/


unix: build_unix
	./$(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME)

osx: build_osx
	./$(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME)

build_osx: main.cpp
	@mkdir -p $(OUTPUT_DIRECTORY)
	$(CC) -o $(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME) *.cpp $(OSX_LINKED_LIBRARIES) $(BASE_LINKED_LIBRARIES)

build_unix: main.cpp
	@mkdir -p $(OUTPUT_DIRECTORY)
	$(CC) -o $(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME) *.*pp $(UNIX_LINKED_LIBRARIES) $(BASE_LINKED_LIBRARIES)

clean:
	rm $(OUTPUT_DIRECTORY)*