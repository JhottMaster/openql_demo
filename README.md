# Open GL Tutorials/Demo
Following Tutorials for OpenGL in C++

## Notes

**Open GL Resources Used**
- http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/
- https://open.gl/introduction
- https://learnopengl.com/Introduction

Other Resources:
https://thebookofshaders.com/

## Ubuntu Setup

Must install necessary dev GLEW, GLFW, and GLM libraries before I could get g++ to link them:
```bash
sudo apt-get install libglew-dev
sudo apt-get install libglfw3-dev
sudo apt-get install libglm-dev
sudo apt-get install libassimp-dev
```

When linking, you can use the gcc `-l[LIBRARY_NAME]` to link the libraries. For example, `-lGL` for OpenGL.

Also, you'll need to download SOIL: https://www.lonesock.net/soil.html  - extract that somewhere and go to `~/project/makefile` directory. Edit the `makefile`'s `CXXFLAGS` variable to do generate position-independent code:
```
CXXFLAGS = -O2 -s -Wall -fpic
```
You may need to uninstall and re-build, in which case you can do that by:
```
sudo make uninstall
sudo make clean
sudo make
```
Then finally run:
```
mkdir obj
sudo make install
```

This will install SOIL in Unix to allow linking. You can't use the library file that comes in `/lib` because it is 32-bit (unless you have a 32-bit machine)

**Note: Version 5 of libassimp-dev is needed to load textures.** If working on an older version of Linux, (like I was), you can forcefull install 5 by following steps here: https://stackoverflow.com/a/60584315/100875

### Building

Build & run with `make unix`

## OSX Setup

Was able to install most of the same libraries as Ubuntu using brew. (eg `brew install glew`, `brew install assimp`). Note that on OSX `gcc` is replaced by Clang compiler, and infact `gcc` actually becomes an alias to it. On OSX linking to OpenGL is also a bit different- you must use `-framework OpenGL` to do so. See make file for more info. We also have a `-framework CoreFoundation` in order to support SOIL:

As with Linux, you'll need to download SOIL: https://www.lonesock.net/soil.html - however, compiling for the latest versions of OSX is a bit different. Extract the download somewhere and go to `~/project/makefile` directory, open `makefile` and make the following change to the `CXX` variable: `CXX = gcc -arch i386 -arch x86_64`; _then_ run
```
mkdir obj
sudo make install
```

This architecture requires the OSX Core Foundation framework, hence the additional linker commmand specified above.

### Building

Build & run with `make osx`

## Windows

Right now this is only tested on Windows 10. To compile, you'll need to do the following:

**Using Visual Studio 2019**

Just open the solution file. 
The special configuratios is mostly in the creation of the `additional_includes` and `additional_libs` directories. GLM you can just download since it's only headers. You'll probably need to build GLEW and SOIL (SOILD Repo: https://github.com/littlstar/soil ) assemblies and place them in `jheatt_engine\additional_libs\x86` if they are not already there. Likewise for Assimp, you'll need to clone the repository, built it **targeting Win32**, (You can do this using Cmake GUI for example) and then copy the `assimp\build\lib\Release\assimp-vc142-mt.lib` generated file to `jheatt_engine\additional_libs\x86` _as well as_ the `assimp\build\bin\Release\assimp-vc142-mt.dll` DLL to the directory where the executable will run (e.g. `jheatt_engine\build\Debug`)

**Other (eg, using `make` or `cmake`)**

I spent a few hours trying to get Windows version to compile and work with just make, MinGW, GLEW, GLFW, and soild, but alas, I couldn't manage it. If feeling adventurous, this looks like a good guide to try again: https://cis.gvsu.edu/~dulimarh/Okto/cis367/

<details><summary>This was the closest I got</summary>
<p>

*Compiler Setup*
1.) Install MinGW- download from: https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/ (Good reference guide here as well: https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html)
2.) After download, use the MinGW Installation Manager to install mingw32-base, mingw-developer-toolchain, mingw32-gcc-g++, and msys-base
3.) Wait a while for all that to finish, then add `C:\MinGW\bin` and `C:\MinGW\msys\1.0\bin` to your PATH enviornment variable.

*GLEW Install*
Download GLEW, unzip, go to main dir and run:
```
mkdir lib
mkdir bin
gcc -DGLEW_NO_GLU -O2 -Wall -W -Iinclude  -DGLEW_BUILD -o src/glew.o -c src/glew.c
gcc -nostdlib -shared -Wl,-soname,libglew32.dll -Wl,--out-implib,lib/libglew32.dll.a    -o lib/glew32.dll src/glew.o -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32
ar cr lib/libglew32.a src/glew.o
```
Details here: https://stackoverflow.com/questions/6005076/building-glew-on-windows-with-mingw

You should now have a `glew32.dll` file you can use under `\lib`- move that binary to the `\lib\win\binaries` folder.

*GLFW Install*
1.) Download GLFW 32-bit binaries: https://www.glfw.org/download.html
2.) Unzip, and navigate to `glfw-3.3.2.bin.WIN32\lib-mingw`
3.) Copy the `glfw3.dll` binary to `\lib\win\binaries` folder

*SOIL Install*

Download https://www.lonesock.net/soil.html

*Last Steps*

Add a new environment variable called `CPATH` that points to `\lib\win\headers` (but use a full path)

</p>
</details>





## Other helpful resources:
- https://open.gl/introduction

