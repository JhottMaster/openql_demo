# Cross-platform compilation:
CC=g++ # Uses clang in OSX
LNK_FLAGS=-lGLEW -lglfw -lSOIL -lassimp -DJHEATT_ENGINE_EXPORTS
OSX_LNK_FLAGS=-framework OpenGL -framework CoreFoundation -std=c++11 -dynamiclib -current_version 1.0 -compatibility_version 1.0
NIX_LNK_FLAGS=-Wall -fpic -lGL
LIB_HEADER_DIR=./additional_includes/

# Build configuration:
LIB_NAME=libjheattengine
SRC_DIR=./jheatt_engine_library/
OUT_DIR=./../build/lib

UNAME_S := $(shell uname -s)
LIB_INSTALL_PATH=/usr/lib
LIB_CONFIG_EXEC=ldconfig
LIB_CHECK=ldconfig -p
ifeq ($(UNAME_S),Linux)
  LIB_NAME := $(LIB_NAME).so
endif
ifeq ($(UNAME_S),Darwin)
  LIB_NAME := $(LIB_NAME).A.dylib
	LIB_INSTALL_PATH=/usr/local/lib
	LIB_CHECK=ls $(LIB_INSTALL_PATH)
	LIB_CONFIG_EXEC=otool -L $(LIB_INSTALL_PATH)/$(LIB_NAME)
endif

unix:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) -shared -o $(OUT_DIR)/$(LIB_NAME) $(shell find -regex './\(jheatt_engine\|headers\|lib\|/\)/*.*pp' -type f) $(NIX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

osx:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) -c $(shell find -E . -type f -regex "./(headers|lib|jheatt_engine).*\.*pp") -fPIC  -DJHEATT_ENGINE_EXPORTS -std=c++11  -I$(LIB_HEADER_DIR)
	$(CC) -o $(OUT_DIR)/$(LIB_NAME) *.o $(LNK_FLAGS) $(OSX_LNK_FLAGS)
	rm *.o || true
	rm headers/*.gch || true
	rm headers/*.gch.tmp || true

install:
	@echo "Make sure to run with sudo! Installing..."
	cp $(OUT_DIR)/$(LIB_NAME) $(LIB_INSTALL_PATH)
	chmod 0755 $(LIB_INSTALL_PATH)/$(LIB_NAME)
	@echo "Loading..."
	$(LIB_CONFIG_EXEC)
	$(LIB_CHECK) | grep $(LIB_NAME)
	@echo "Done!"

uninstall:
	@echo "Make sure to run with sudo! Uninstalling..."
	rm $(LIB_INSTALL_PATH)/$(LIB_NAME)
	@echo "Done!"

clean:
	rm -r $(OUT_DIR)/* || true