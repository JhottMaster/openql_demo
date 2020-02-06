# Cross-platform compilation:
CC=g++
BASE_LINKED_LIBRARIES=-lGLEW -lglfw -lSOIL
OSX_LINKED_LIBRARIES=-framework OpenGL -framework CoreFoundation
UNIX_LINKED_LIBRARIES=-Wall -lGL
LOCAL_INCLUDE_PATH=./additional_includes/

# Build configuration:
EXECUTABLE_NAME=open_gl_demo

SOURCE_DIRECTORY=./open_gl_demo/
BUILD_DIRECTORY=./open_gl_demo/build/bin/
OUTPUT_DIRECTORY=./open_gl_demo/build/




unix: build_unix
	cp -u -r $(SOURCE_DIRECTORY)shaders $(OUTPUT_DIRECTORY)shaders
	cp -u -r $(SOURCE_DIRECTORY)resources $(OUTPUT_DIRECTORY)resources
	cd $(OUTPUT_DIRECTORY); ./$(EXECUTABLE_NAME)

osx: build_osx
	cp -f -R $(SOURCE_DIRECTORY)shaders $(OUTPUT_DIRECTORY)shaders
	cp -f -R $(SOURCE_DIRECTORY)resources $(OUTPUT_DIRECTORY)resources
	cd $(OUTPUT_DIRECTORY); ./$(EXECUTABLE_NAME)

build_osx:
	@mkdir -p $(OUTPUT_DIRECTORY)
	$(CC) -o $(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME) $(SOURCE_DIRECTORY)*.cpp $(OSX_LINKED_LIBRARIES) $(BASE_LINKED_LIBRARIES) -I$(LOCAL_INCLUDE_PATH)

build_unix:
	@mkdir -p $(OUTPUT_DIRECTORY)
	$(CC) -o $(OUTPUT_DIRECTORY)$(EXECUTABLE_NAME) $(SOURCE_DIRECTORY)*.*pp $(UNIX_LINKED_LIBRARIES) $(BASE_LINKED_LIBRARIES) -I$(LOCAL_INCLUDE_PATH)

win: build_windows
	copy 
	$(OUTPUT_DIRECTORY)\$(EXECUTABLE_NAME).exe

build_windows: $(SOURCE_DIRECTORY)main.cpp
	if not exist $(OUTPUT_DIRECTORY)\ mkdir $(OUTPUT_DIRECTORY)\;
	$(CC) -o $(OUTPUT_DIRECTORY)\$(EXECUTABLE_NAME).exe *.*pp -L"lib\win\binaries" -Bstatic -lSOIL -lopengl32 -lglfw3 -lglew32 -mwindows 

clean:
	rm $(OUTPUT_DIRECTORY)*