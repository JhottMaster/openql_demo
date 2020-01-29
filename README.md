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

### Building

Build & run with `make unix`

## OSX Setup

Was able to install most of the same libraries as Ubuntu using brew. (eg `brew install glew`). Note that on OSX `gcc` is replaced by Clang compiler, and infact `gcc` actually becomes an alias to it. On OSX linking to OpenGL is also a bit different- you must use `-framework OpenGL` to do so. See make file for more info. 

### Building

Build & run with `make osx`

## Other helpful resources:
- https://open.gl/introduction

