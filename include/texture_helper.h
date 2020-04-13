#ifndef TEXTURE_HELPER_H
# define TEXTURE_HELPER_H
# include <glad/glad.h>
# include <GLFW/glfw3.h>

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
	struct s_texture	*(*bind)(struct s_texture *tex, int gl_tex_target, int texture_unit);
	struct s_texture	*(*set_params)(struct s_texture *tex);
	int					(*exec)(struct s_texture *tex);
	void				(*destroy)(struct s_texture **tex);
}						t_texture;

t_texture				*texture_construct();

#endif
