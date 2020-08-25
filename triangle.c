#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "shader_utils.h"

GLuint program;
GLint attribute_coord2d;

int		init_resources(void)
{
	GLint compile_ok = GL_FALSE, link_ok = GL_FALSE;

	GLuint vs, fs;
	if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0) return 0;
	if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0;

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram: ");
		print_log(program);
		return 0;
	}

	const char* attribute_name = "coord2d";
	attribute_coord2d = glGetAttribLocation(program, attribute_name);
	if (attribute_coord2d == -1) {
		fprintf(stderr, "Could not bind attribute %s %d", attribute_name, glGetError());
		return 0;
	}

	return 1;
}

void	render(SDL_Window *window)
{
	/* Clear the background as white */
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(program);
	glEnableVertexAttribArray(attribute_coord2d);
	GLfloat triangle_vertices[] = {
	   -1.0,  0.999,
	   -0.5, -0.5,
	    0.999, -1.0,
	};
	GLfloat triangle2_vertices[] = {
	   -0.999,  1.0,
	    0.5,  0.5,
	    1.0, -0.999,
	};
	/* Describe our vertices array to OpenGL (it can't guess its format automatically) */
	glVertexAttribPointer(
		attribute_coord2d, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		triangle_vertices  // pointer to the C array
						  );

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glVertexAttribPointer(
		attribute_coord2d, // attribute
		2,                 // number of elements per vertex, here (x,y)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		triangle2_vertices // pointer to the C array
						  );

	/* Push each element in buffer_vertices to the vertex shader */
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableVertexAttribArray(attribute_coord2d);

	/* Display the result */
	SDL_GL_SwapWindow(window);
}

void	free_resources()
{
	glDeleteProgram(program);
}

void	mainloop(SDL_Window *window) {
	while (1)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			if (ev.type == SDL_QUIT)
				return;
		}
		render(window);
	}
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("Triangle",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 640,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	SDL_GL_CreateContext(window);

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: glewInit: %s", glewGetErrorString(glew_status));
		return (EXIT_FAILURE);
	}

	if (!init_resources())
		return EXIT_FAILURE;

	mainloop(window);

	free_resources();
	return (EXIT_SUCCESS);
}
