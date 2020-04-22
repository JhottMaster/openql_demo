# Cross-platform compilation:
CC=g++ # Uses clang in OSX
LNK_FLAGS=-lGLEW -lglfw -lassimp
OSX_LNK_FLAGS= -framework OpenGL -framework CoreFoundation /usr/local/lib/libjheattengine.A.dylib -std=c++11
NIX_LNK_FLAGS=-Wall -lGL -ljheattengine
LIB_HEADER_DIR=-I ./../jheatt_engine_library/headers/

# Build configuration:
EXEC_NAME=jheatt_demo
SRC_DIR=./jheatt_engine_demo/
OUT_DIR=./../build/demo

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  OUT_DIR=./../build
endif

unix: create_unix_dirs	
	@echo "Finished! Running:"
	cd $(OUT_DIR)/; ./$(EXEC_NAME)

create_unix_dirs: build_unix
	@echo "Creating output dirs..."
	rm -f -r $(OUT_DIR)/shaders
	cp -u -r ./shaders $(OUT_DIR)
	cp -u -r -a ./resources $(OUT_DIR)

osx: create_osx_dirs
	@echo "Finished! Running:"
	cd $(OUT_DIR)/; ./$(EXEC_NAME)

create_osx_dirs: build_osx
	@echo "Moving & renaming executable (a.out)..."
	mv ./a.out $(OUT_DIR)/$(EXEC_NAME)
	@echo "Creating output dirs..."
	rm -f -r $(OUT_DIR)/shaders
	cp -f -R ./shaders $(OUT_DIR)/shaders
	cp -f -R ./resources $(OUT_DIR)/resources

build_osx:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) $(shell find '.' -name '*.*pp') $(OSX_LNK_FLAGS) $(LNK_FLAGS) $(LIB_HEADER_DIR)

build_unix:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) -o $(OUT_DIR)/$(EXEC_NAME) $(shell find -regex '$(SRC_DIR)*.*pp' -type f) $(NIX_LNK_FLAGS) $(LNK_FLAGS) $(LIB_HEADER_DIR)

clean:
	rm -r $(OUT_DIR)/* || true