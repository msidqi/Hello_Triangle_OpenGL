#ifndef SCOP_H
# define SCOP_H
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <stdio.h>
# include <stdlib.h>
# include "shaders.h"
# include "texture_helper.h"
# include "libgl.h"
# include "libft.h"
# include "parser.h"

typedef struct		s_wind
{
	GLFWwindow		*window;
}					t_wind;

typedef struct		s_env
{
	t_texture		*tex;
	t_mat4f 		final_matrix;
	t_obj			*obj;
	t_shader		*shader;
	GLFWwindow		*window;
	unsigned int	VBO;
	unsigned int	VAO;
	// used for indexed-drawing
	unsigned int	EBO;
}					t_env;

typedef struct		s_event_handler
{
	double			rel_mouse_ypos;
	double			rel_mouse_xpos;
	double			mouse_xpos_old;
	double			mouse_ypos_old;
	int				isScaleMode;
	int				isLeftClick;
	int				isRightClick;
	float			mixValue;
	float			scaleFactor;
	t_vec3f			translation;
	t_vec3f			rotation;
	float			rot_angle;
}					t_event_handler;

void				processInput(GLFWwindow *window);
void				scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void				cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void				mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void				framebuffer_size_callback(GLFWwindow* window, int width, int height);
t_event_handler		*ft_event_handler_init();

void				ft_fps_print();

int					init_setup(GLFWwindow **window, int width, int height, char *window_name);

#endif