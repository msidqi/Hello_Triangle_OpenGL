/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:29:29 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:29:50 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H
# include "libgl.h"
# include "libft.h"
# include "glad.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_shader
{
	unsigned int	program_id;
	unsigned int	vertex_id;
	unsigned int	fragment_id;
	void			(*use)(struct s_shader *this);
	void			(*set_int)(struct s_shader *this,
						const char *name, const int value);
	void			(*set_float)(struct s_shader *this,
						const char *name, const float value);
	void			(*set_vec2)(struct s_shader *this,
						const char *name, const t_vec2f *value);
	void			(*set_vec2f)(struct s_shader *this,
						const char *name, float x, float y);
	void			(*set_vec3)(struct s_shader *this,
						const char *name, const t_vec3f *value);
	void			(*set_vec3f)(struct s_shader *this,
						const char *name, float x, float y, float z);
	void			(*set_vec4)(struct s_shader *this,
						const char *name, const t_vec4f *value);
	void			(*set_vec4f)(struct s_shader *this,
						const char *name, float x, float y, float z, float w);
	void			(*set_mat4f)(struct s_shader *this,
						const char *name, const t_mat4f *mat);
}					t_shader;

t_shader			*shader_construct(const char *vshader_path,
											const char *fshader_path);
char				*read_shader_file(const char *file_name);
void				use_shader_program(t_shader *this);
void				init_shader(t_shader *this);

#endif
