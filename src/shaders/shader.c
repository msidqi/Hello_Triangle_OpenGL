#include "../../include/shaders.h"

char	*read_shader_file(const char *file_name)
{
	FILE		*fd;
	char		*shader_buffer;
	size_t		shader_size;//, log_size;

	if ((fd = fopen(file_name, "r")) == NULL)
	{
		printf("ERROR::OPEN::COULD_NOT_OPEN_FILE : %s\n", file_name);
		return(NULL);
	}
	fseek(fd, 0, SEEK_END);
	shader_size = ftell(fd);
	rewind(fd);
	if (!(shader_buffer = (char *)malloc(shader_size + 1)))
	{
		printf("ERROR::MALLOC::OUT_OF_MEMORY\n");
		return (NULL);
	}
	shader_buffer[shader_size] = '\0';
	fread(shader_buffer, sizeof(char), shader_size, fd);
	fclose(fd);
	return (shader_buffer);
}

int		create_compile_shader(char *shader_source, unsigned int *shader, int shader_type)
{
	int  success;
	char info_log[512];
	const char *type = (shader_type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";

	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, (const char *const*)&shader_source, NULL); // 1: how many strings are passed as src code
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", type, info_log);
		return (0);
	}
	return (1);
}

int		create_link_program(unsigned int *shader_program, unsigned int vshader, unsigned int fshader)
{
	int  success;
	char info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vshader);
	glAttachShader(*shader_program, fshader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", info_log);
		return (0);
	}
	return (1);
}

void		use_shader_program(t_shader *this)
{
	glUseProgram(this->program_id);
}

void set_int(struct s_shader *this, const char *name, int value)
{ 
    glUniform1i(glGetUniformLocation(this->program_id, name), value); 
}
// ------------------------------------------------------------------------
void set_float(struct s_shader *this, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(this->program_id, name), value); 
}
// ------------------------------------------------------------------------
void set_vec2(struct s_shader *this, const char *name, const t_vec2f *vec)
{ 
	glUniform2fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]);
}
// ------------------------------------------------------------------------
void set_vec2f(struct s_shader *this, const char *name, float x, float y)
{ 
	glUniform2f(glGetUniformLocation(this->program_id, name), x, y); 
}
// ------------------------------------------------------------------------
void set_vec3(struct s_shader *this, const char *name, const t_vec3f *vec)
{ 
	glUniform3fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}
void set_vec3f(struct s_shader *this, const char *name, float x, float y, float z)
{ 
	glUniform3f(glGetUniformLocation(this->program_id, name), x, y, z); 
}
// ------------------------------------------------------------------------
void set_vec4(struct s_shader *this, const char *name, const t_vec4f *vec)
{ 
	glUniform4fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}
void set_vec4f(struct s_shader *this, const char *name, float x, float y, float z, float w)
{ 
	glUniform4f(glGetUniformLocation(this->program_id, name), x, y, z, w); 
}
// ------------------------------------------------------------------------
void set_mat4f(struct s_shader *this, const char *name, const t_mat4f *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program_id, name), 1, GL_FALSE, (const GLfloat *)&mat->v);
}
// ------------------------------------------------------------------------
/*void set_Mat2(struct s_shader *this, const char *name, const t_mat2 *mat)
{
	glUniformMatrix2fv(glGetUniformLocation(this->program_id, name), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void set_Mat3(struct s_shader *this, const char *name, const t_mat3 *mat)
{
	glUniformMatrix3fv(glGetUniformLocation(this->program_id, name), 1, GL_FALSE, &mat[0][0]);
}*/

t_shader	*shader_construct(const char *vshader_path, const char *fshader_path)
{
	t_shader		*this;
	char			*vshader_source;
	unsigned int	vshader;
	char			*fshader_source;
	unsigned int	fshader;

	if (!(this = (t_shader *)malloc(sizeof(t_shader))))
		return (NULL);
	if (!(vshader_source = read_shader_file(vshader_path))
	|| !create_compile_shader(vshader_source, &vshader, GL_VERTEX_SHADER))
		return NULL;
	free(vshader_source);
	if (!(fshader_source = read_shader_file(fshader_path))
	|| !create_compile_shader(fshader_source, &fshader, GL_FRAGMENT_SHADER))
		return NULL;
	free(fshader_source);
	if (!(create_link_program(&this->program_id, vshader, fshader)))
		return (NULL);
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	this->use = &use_shader_program;
	this->set_int = &set_int;
	this->set_float = &set_float;
	this->set_vec2 = &set_vec2;
	this->set_vec2f = &set_vec2f;
	this->set_vec3 = &set_vec3;
	this->set_vec3f = &set_vec3f;
	this->set_vec4 = &set_vec4;
	this->set_vec4f = &set_vec4f;
	this->set_mat4f = &set_mat4f;
	return (this);
}