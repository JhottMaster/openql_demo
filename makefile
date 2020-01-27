all: open_gl_demo
	./build/open_gl_demo

open_gl_demo:  main.cpp
	 gcc -o build/open_gl_demo *.*pp -lGLEW -lglfw -lGL

open_gl_demo.o: main.cpp
	 gcc -c -o build/main.o main.cpp
	 gcc -c -o build/window_manager.o window_manager.hpp
     
clean:
	 rm build/*