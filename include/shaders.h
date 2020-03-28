#ifndef SHADERS_H
# define SHADERS_H

typedef struct		s_shader
{
	unsigned int	program_id;
	unsigned int	vertex_id;
	unsigned int	fragment_id;
	void			(*use)(struct s_shader *this);
	void			(*setInt)(struct s_shader *this, const char *name, int value);
	void			(*setFloat)(struct s_shader *this, const char *name, float value);
}					t_shader;

t_shader	*shader_contruct(const char *vshader_path, const char *fshader_path);
char		*read_shader_file(const char *file_name);

#endif