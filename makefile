# Cross-platform compilation:
CC=g++
LNK_FLAGS=-lGLEW -lglfw -lSOIL
OSX_LNK_FLAGS=-framework OpenGL -framework CoreFoundation
NIX_LNK_FLAGS=-Wall -lGL
LIB_HEADER_DIR=./additional_includes/

# Build configuration:
EXEC_NAME=open_gl_demo

SRC_DIR=./jheatt_engine/
OUT_DIR=./build/
SRC_FILES := $(shell find -regex '$(SRC_DIR)*.*pp' -type f)

unix: build_unix
	@echo "Creating output dirs..."
	cp -u -r $(SRC_DIR)shaders $(OUT_DIR)shaders
	cp -u -r $(SRC_DIR)resources $(OUT_DIR)resources
	@echo "Finished! Running:"
	cd $(OUT_DIR); ./$(EXEC_NAME)

osx: build_osx
	@echo "Creating output dirs..."
	cp -f -R $(SRC_DIR)shaders $(OUT_DIR)shaders
	cp -f -R $(SRC_DIR)resources $(OUT_DIR)resources
	@echo "Finished! Running:"
	cd $(OUT_DIR); ./$(EXEC_NAME)

build_osx:
	@mkdir -p $(OUT_DIR)
	@echo "Building..."
	$(CC) -o $(OUT_DIR)$(EXEC_NAME) $(SRC_FILES) $(OSX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

build_unix:
	@mkdir -p $(OUT_DIR)
	@echo "Building..."
	$(CC) -o $(OUT_DIR)$(EXEC_NAME) $(SRC_FILES) $(NIX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

clean:
	rm $(OUT_DIR)*