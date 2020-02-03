# Open GL Tutorials/Demo
Following Tutorials for OpenGL in C++

## Tutorials & Notes

**Tutorial 1**
- http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
  - Refactored a lot of the window setup code to its own class & improved code readability.

## Ubuntu Setup

Must install necessary dev GLEW, GLFW, and GLM libraries before I could get g++ to link them:
```bash
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev
sudo apt-get install libglm-dev
```

When linking, you can use the gcc `-l[LIBRARY_NAME]` to link the libraries. For example, `-lGL` for OpenGL.

Also, you'll need to download SOIL: https://www.lonesock.net/soil.html  - extract that somewhere and go to `~/project/makefile` directory, and the run:
```
mkdir obj
sudo make install
```

This will install SOIL in Unix to allow linking. You can't use the library file that comes in `/lib` because it is 32-bit (unless you have a 32-bit machine)

### Building

Build & run with `make unix`

## OSX Setup

Was able to install most of the same libraries as Ubuntu using brew. (eg `brew install glew`). Note that on OSX `gcc` is replaced by Clang compiler, and infact `gcc` actually becomes an alias to it. On OSX linking to OpenGL is also a bit different- you must use `-framework OpenGL` to do so. See make file for more info. We also have a `-framework CoreFoundation` in order to support SOIL:

As with Linux, you'll need to download SOIL: https://www.lonesock.net/soil.html - however, compiling for the latest versions of OSX is a bit different. Extract the download somewhere and go to `~/project/makefile` directory, open `makefile` and make the following change to the `CXX` variable: `CXX = gcc -arch i386 -arch x86_64`; _then_ run
```
mkdir obj
sudo make install
```

This architecture requires the OSX Core Foundation framework, hence the additional linker commmand specified above.

### Building

Build & run with `make osx`

## Other helpful resources:
- https://open.gl/introduction

