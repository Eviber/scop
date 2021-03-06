#include <GL/glew.h>
#include <SDL2/SDL.h>

/**
 * Store all the file's contents in memory, useful to pass shaders
 * source code to OpenGL. Using SDL_RWops for Android asset support.
 */

char	*file_read(const char *filename)
{
	SDL_RWops	*rw = SDL_RWFromFile(filename, "rb");
	if (rw == NULL)
		return (NULL);

	Sint64 res_size = SDL_RWsize(rw);
	char *res = (char *)malloc(res_size + 1); // TODO ft_strnew

	Sint64 nb_read_total = 0, nb_read = 1;
	char *buf = res;
	while (nb_read_total < res_size && nb_read != 0)
	{
		nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
		nb_read_total += nb_read;
		buf += nb_read; // ???
	}
	SDL_RWclose(rw);
	if (nb_read_total != res_size)
	{
		free(res);
		return (NULL);
	}
	res[nb_read_total] = '\0';
	return (res);
}

/**
 * Display compilation errors from the OpenGL shader compiler
 */

void	print_log(GLuint object)
{
	GLint	log_length = 0;

	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else
	{
		fprintf(stderr, "printlog: Not a shader or a program.\n");
		return;
	}

	char *log = (char *)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else
		glGetProgramInfoLog(object, log_length, NULL, log);
	fprintf(stderr, log);
	free(log);
}

GLuint	create_shader(const char *filename, GLenum type)
{
	const GLchar *source = file_read(filename);
	if (source == NULL)
	{
		fprintf(stderr, "Error opening %s: %s\n", filename, SDL_GetError());
		return (0);
	}
	GLuint res = glCreateShader(type);
	const GLchar *sources[] = {
#ifdef GL_ES_VERSION_2_0
		"#version 100\n" // OpenGL ES 2.0
#else
		"#version 120\n" // OpenGL 2.1
#endif
		,
		source };
	glShaderSource(res, 2, sources, NULL);
	free((void *)source);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE)
	{
		fprintf(stderr, "%s:", filename);
		print_log(res);
		glDeleteShader(res);
		return (0);
	}

	return (res);
}
