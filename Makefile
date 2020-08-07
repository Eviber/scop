LDLIBS= -lGLEW -lGL -lSDL2
all: triangle
	gcc triangle.c `sdl2-config --libs --cflags` -lGLEW -lGL -o triangle
clean:
	rm -f *.o triangle
.PHONY: all clean
