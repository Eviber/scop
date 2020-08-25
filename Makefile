LDLIBS= -lGLEW -lGL -lSDL2
triangle:
	gcc -g3 -c shader_utils.c -o shader_utils.o
	gcc -g3 -c triangle.c -o triangle.o
all: triangle
	gcc -g triangle.o shader_utils.o `sdl2-config --libs --cflags` -lGLEW -lGL -o triangle
clean:
	rm -f *.o triangle
.PHONY: all clean
