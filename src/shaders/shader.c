#include "shaders.h"
#include <glad/glad.h> 
#include <stdio.h>
#include <stdlib.h>

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
	free(shader_source);
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
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	return (1);
}

void		use_shader_program(t_shader *this)
{
	glUseProgram(this->program_id);
}

void setInt(struct s_shader *this, const char *name, int value)
{ 
    glUniform1i(glGetUniformLocation(this->program_id, name), value); 
}
void setFloat(struct s_shader *this, const char *name, float value)
{ 
    glUniform1f(glGetUniformLocation(this->program_id, name), value); 
}

t_shader	*shader_contruct(const char *vshader_path, const char *fshader_path)
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
	if (!(fshader_source = read_shader_file(fshader_path))
	|| !create_compile_shader(fshader_source, &fshader, GL_FRAGMENT_SHADER))
		return NULL;
	if (!(create_link_program(&this->program_id, vshader, fshader)))
		return (NULL);
	this->use = &use_shader_program;
	this->setInt = &setInt;
	this->setFloat = &setFloat;
	return (this);
}