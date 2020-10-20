/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:21:26 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:27:11 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H
# include "glad.h"
# include <GLFW/glfw3.h>
# include <stdio.h>
# include <stdlib.h>
# include "shaders.h"
# include "texture_helper.h"
# include "libgl.h"
# include "libft.h"
# include "parser.h"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct		s_wind
{
	GLFWwindow		*window;
}					t_wind;

typedef struct		s_event_handler
{
	double			rel_mouse_ypos;
	double			rel_mouse_xpos;
	double			mouse_xpos_old;
	double			mouse_ypos_old;
	int				is_scale_mode;
	int				is_rot_mode;
	int				is_smooth_transition;
	float			initial_trans_time;
	int				is_left_click;
	int				is_right_click;
	float			mix_value;
	float			scale_factor;
	t_vec3f			translation;
	float			translation_mod;
	t_vec3f			rotation;
	float			rot_angle;
	int				width;
	int				height;
}					t_event_handler;

/*
**  used for indexed-drawing
** 	GLuint			ebo;
*/
typedef struct		s_env
{
	t_event_handler	*e_handler;
	t_texture		*tex;
	t_mat4f			final_matrix;
	t_obj			*obj;
	t_shader		*shader;
	GLFWwindow		*window;
	GLuint			vbo;
	GLuint			vao;
	GLuint			ebo;
}					t_env;

t_event_handler		*ft_event_handler_init();
void				process_input(GLFWwindow *window);
void				scroll_callback(GLFWwindow *window,
											double xoffset, double yoffset);
void				cursor_position_callback(GLFWwindow *window,
											double xpos, double ypos);
void				mouse_button_callback(GLFWwindow *window,
											int button, int action, int mods);
void				framebuffer_size_callback(GLFWwindow *window,
											int width, int height);

void				ft_fps_print();

int					init_opengl(GLFWwindow **window, int width,
											int height, char *window_name);

#endif
