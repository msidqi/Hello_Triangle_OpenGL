#ifndef SCOP_H
#define SCOP_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
// #include "texture_helper.h"

typedef struct	s_wind
{
	GLFWwindow* window;
}				t_wind;

typedef struct			s_texture
{
	int 				w;
	int					h;
	int					channels;
	unsigned char		*data;
	unsigned int		gl_id;
	int					gl_target;
	int					error;
	struct s_texture	*(*load)(struct s_texture *tex, char *texture_path);
	struct s_texture	*(*bind)(struct s_texture *tex, int gl_target, int texture_number);
	struct s_texture	*(*set_params)(struct s_texture *tex);
	void				(*exec)(struct s_texture *tex);
	void				(*destroy)(struct s_texture *tex);
}						t_texture;

t_texture				*texture_contruct();

#endif