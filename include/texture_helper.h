#ifndef TEXTURE_HELPER_H
# define TEXTURE_HELPER_H
# include <glad/glad.h>
# include <GLFW/glfw3.h>

enum e_tex_wrap
{
	WRAP_R = GL_REPEAT,
	WRAP_MR = GL_MIRRORED_REPEAT,
	WRAP_CE = GL_CLAMP_TO_EDGE,
	WRAP_CB = GL_CLAMP_TO_BORDER,
};

enum e_tex_filter
{
	FILTER_N = GL_NEAREST,
	FILTER_L = GL_LINEAR,
	FILTER_NML = GL_NEAREST_MIPMAP_LINEAR,
	FILTER_NMN = GL_NEAREST_MIPMAP_NEAREST,
	FILTER_LML = GL_LINEAR_MIPMAP_LINEAR,
	FILTER_LMN = GL_LINEAR_MIPMAP_NEAREST,
};

typedef struct			s_tex_params
{
	unsigned int		wrap_s; // x axis
	unsigned int		wrap_t; // y axis
	unsigned int		wrap_r; // z (only for 3D)
	unsigned int		filter_min;
	unsigned int		filter_mag;
}						t_tex_params;

typedef struct			s_texture
{
	int 				w;
	int					h;
	int					channels;
	unsigned char		*data;
	unsigned int		bind_id;
	unsigned int		gl_id;
	int					gl_target;
	int					error;
	struct s_texture	*(*load)(struct s_texture *tex, char *texture_path);
	struct s_texture	*(*bind)(struct s_texture *tex, int gl_tex_target, int texture_unit);
	struct s_texture	*(*set_params)(struct s_texture *tex, t_tex_params options);
	int					(*exec)(struct s_texture *tex);
	void				(*destroy)(struct s_texture **tex);
}						t_texture;

t_texture				*texture_construct();

#endif
