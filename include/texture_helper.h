/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_helper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:32:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/12 18:57:52 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HELPER_H
# define TEXTURE_HELPER_H
# include "glad.h"
# include <GLFW/glfw3.h>
# include <stdlib.h>

enum					e_tex_wrap
{
	WRAP_R = GL_REPEAT,
	WRAP_MR = GL_MIRRORED_REPEAT,
	WRAP_CE = GL_CLAMP_TO_EDGE,
	WRAP_CB = GL_CLAMP_TO_BORDER,
};

enum					e_tex_filter
{
	FILTER_N = GL_NEAREST,
	FILTER_L = GL_LINEAR,
	FILTER_NML = GL_NEAREST_MIPMAP_LINEAR,
	FILTER_NMN = GL_NEAREST_MIPMAP_NEAREST,
	FILTER_LML = GL_LINEAR_MIPMAP_LINEAR,
	FILTER_LMN = GL_LINEAR_MIPMAP_NEAREST,
};

/*
**	wrap_s; // x axis
**	wrap_t; // y axis
**	wrap_r; // z (only for 3D)
*/

typedef struct			s_tex_params
{
	unsigned int		wrap_s;
	unsigned int		wrap_t;
	unsigned int		wrap_r;
	unsigned int		filter_min;
	unsigned int		filter_mag;
}						t_tex_params;

typedef struct			s_texture
{
	int					w;
	int					h;
	int					channels;
	unsigned char		*data;
	unsigned int		bind_id;
	unsigned int		gl_id;
	int					gl_target;
	int					error;
	struct s_texture	*(*load)(struct s_texture *tex,
								char *texture_path);
	struct s_texture	*(*bind)(struct s_texture *tex,
								int gl_tex_target, int texture_unit);
	struct s_texture	*(*set_params)(struct s_texture *tex,
								t_tex_params options);
	int					(*exec)(struct s_texture *tex);
	void				(*destroy)(struct s_texture **tex);
}						t_texture;

t_texture				*texture_construct(void);
t_texture				*load(t_texture *this, char *texture_path);
t_texture				*bind(t_texture *this,
								int gl_tex_target, int texture_unit);
t_texture				*set_params(t_texture *this, t_tex_params opts);
int						exec(t_texture *this);
void					tex_destroy(t_texture **this);

#endif
