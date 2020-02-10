# Cross-platform compilation:
CC=g++ # Uses clang in OSX
LNK_FLAGS=-lGLEW -lglfw -lSOIL
OSX_LNK_FLAGS=-framework OpenGL -framework CoreFoundation -std=c++11
NIX_LNK_FLAGS=-Wall -lGL
LIB_HEADER_DIR=./additional_includes/

# Build configuration:
EXEC_NAME=jheatt_engine
SRC_DIR=./jheatt_engine
OUT_DIR=./build

unix: build_unix
	@echo "Creating output dirs..."
	rm -r $(OUT_DIR)/shaders
	cp -u -r $(SRC_DIR)/shaders $(OUT_DIR)/shaders
	cp -u -r -a $(SRC_DIR)/resources $(OUT_DIR)/resources
	@echo "Finished! Running:"
	cd $(OUT_DIR)/; ./$(EXEC_NAME)

osx: build_osx
	@echo "Moving & renaming executable (a.out)..."
	mv ./a.out $(OUT_DIR)/$(EXEC_NAME)
	@echo "Creating output dirs..."
	rm -r $(OUT_DIR)/shaders
	cp -f -R $(SRC_DIR)/shaders $(OUT_DIR)/shaders
	cp -f -R $(SRC_DIR)/resources $(OUT_DIR)/resources
	@echo "Finished! Running:"
	cd $(OUT_DIR)/; ./$(EXEC_NAME)

build_osx:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) $(shell find '$(SRC_DIR)' -name '*.*pp') $(OSX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

build_unix:
	@mkdir -p $(OUT_DIR)/
	@echo "Building..."
	$(CC) -o $(OUT_DIR)/$(EXEC_NAME) $(shell find -regex '$(SRC_DIR)*.*pp' -type f) $(NIX_LNK_FLAGS) $(LNK_FLAGS) -I$(LIB_HEADER_DIR)

clean:
	rm -r $(OUT_DIR)/*