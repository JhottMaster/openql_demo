# Cross-platform compilation:
CC=g++ # Uses clang in OSX
LNK_FLAGS=-lGLEW -lglfw -lSOIL -lassimp
OSX_LNK_FLAGS=-framework OpenGL -framework CoreFoundation -std=c++11 -dynamiclib -fPIC -DJHEATT_ENGINE_EXPORTS
NIX_LNK_FLAGS=-Wall -fpic -lGL -DJHEATT_ENGINE_EXPORTS
LIB_HEADER_DIR=./additional_includes/

# Build configuration:
LIB_NAME=libjheattengine
SRC_DIR=./jheatt_engine_library/
OUT_DIR=./../build/lib

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  LIB_NAME := $(LIB_NAME).so
endif
ifeq ($(UNAME_S),Darwin)
  LIB_NAME := $(LIB_NAME).dylib
endif

BUILD_COMMAND := $(CC) -shared -o $(OUT_DIR)/$(LIB_NAME) $(shell find -regex './\(jheatt_engine\|headers\|lib\|/\)/*.*pp' -type f)

test:
	@echo "Output file name: $(LIB_NAME)"

unix:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(BUILD_COMMAND) $(NIX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

osx:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(BUILD_COMMAND) $(OSX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

install:
	@echo "Make sure to run with sudo! Installing..."
	cp $(OUT_DIR)/$(LIB_NAME) /usr/lib
	chmod 0755 /usr/lib/$(LIB_NAME)
	@echo "Loading..."
	ldconfig
	ldconfig -p | grep $(LIB_NAME)
	@echo "Done!"

uninstall:
	@echo "Make sure to run with sudo! Uninstalling..."
	rm /usr/lib/$(LIB_NAME)

clean:
	rm -r $(OUT_DIR)/*