/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:21:26 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/15 14:53:56 by msidqi           ###   ########.fr       */
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
# define WINDOW_NAME "Scop"
# define VERTEX_SHADER_PATH "src/shaders/shaderSource/vertex.glsl"
# define FRAGEMENT_SHADER_PATH "src/shaders/shaderSource/fragment.glsl"

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
	float			noise_coef;
	int				is_shading;
	float			is_smooth_noise_transition;
	float			scale_factor;
	t_vec3f			translation;
	float			translation_mod;
	t_vec3f			rotation;
	float			rot_angle;
	int				width;
	int				height;
}					t_event_handler;

typedef struct		s_buffer_params
{
	GLuint			location;
	GLint			number_of_elements;
	GLenum			gl_type;
	GLboolean		normalized;
	GLsizei			stride;
	GLuint			index_in_stride;
	unsigned long	type_size;
}					t_bp;

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
	char			*vs_path;
	char			*fs_path;
}					t_env;


void				main_loop(t_env *e);

/*
** ----------------- events ----------------
*/

void				ft_event_handler_init(t_env *env);
t_event_handler		*get_event_handler(void);

/*
** ----------------- events callbacks ----------------
*/

void				process_input(GLFWwindow *window, t_event_handler *e);
void				scroll_callback(GLFWwindow *window,
											double xoffset, double yoffset);
void				cursor_position_callback(GLFWwindow *window,
											double xpos, double ypos);
void				mouse_button_callback(GLFWwindow *window,
											int button, int action, int mods);
void				framebuffer_size_callback(GLFWwindow *window,
											int width, int height);
void				key_callback(GLFWwindow *window,
								int key, int scancode, int action, int mods);
void				ft_handle_key_press(t_event_handler *e, int key);

/*
** ----------------- debug ----------------
*/

void				ft_fps_print();

/*
** ----------------- opengl ----------------
*/

int					init_opengl(GLFWwindow **window, int width,
											int height, char *window_name);

t_texture			*load_texture(char *path, t_shader *shader);
void				ft_model_world_view(t_event_handler *e, t_mat4f *result);
void				handle_buffers(t_env *env);

void				bind_vao(GLuint vao);
void				generate_vao(GLuint *vao);
void				bind_buffer(GLuint target_buffer, GLuint buffer,
						unsigned long buffer_size, const void *data);
void				generate_buffer(unsigned int *vbo);
void				describe_buffer(t_bp params);

#endif
