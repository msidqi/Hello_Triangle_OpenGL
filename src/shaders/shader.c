/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:28:53 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/24 17:04:48 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shaders.h"

char		*read_shader_file(const char *file_name)
{
	FILE		*fd;
	char		*shader_buffer;
	size_t		shader_size;

	if ((fd = fopen(file_name, "r")) == NULL)
	{
		ft_putstr_fd("ERROR::OPEN::COULD_NOT_OPEN_FILE : ", 2);
		ft_putendl_fd(file_name, 2);
		return (NULL);
	}
	fseek(fd, 0, SEEK_END);
	shader_size = ftell(fd);
	rewind(fd);
	if (!(shader_buffer = (char *)malloc(shader_size + 1)))
	{
		ft_putendl_fd("ERROR::MALLOC::COULD NOT ALLOCATE MEMORY", 2);
		return (NULL);
	}
	shader_buffer[shader_size] = '\0';
	fread(shader_buffer, sizeof(char), shader_size, fd);
	fclose(fd);
	return (shader_buffer);
}

/*
** glShaderSource(*shader, 1, (const char *const*)&shader_source, NULL);
** 1: how many strings are passed as src code
*/

int			create_compile_shader(
	char *shader_source,
	unsigned int *shader,
	int shader_type)
{
	int			success;
	char		info_log[512];
	const char	*type = (shader_type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGM";

	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, (const char *const*)&shader_source, NULL);
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", type, info_log);
		return (0);
	}
	return (1);
}

int			create_link_program(
	unsigned int *shader_program,
	unsigned int vshader,
	unsigned int fshader)
{
	int		success;
	char	info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vshader);
	glAttachShader(*shader_program, fshader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		ft_putstr_fd("ERROR::PROGRAM::LINKING_FAILED :", 2);
		ft_putendl_fd(info_log, 2);
		return (0);
	}
	return (1);
}

void		use_shader_program(t_shader *this)
{
	glUseProgram(this->program_id);
}

t_shader	*shader_construct(
	const char *vshader_path,
	const char *fshader_path)
{
	t_shader		*this;
	char			*shader_src[2];
	unsigned int	shader_ids[2];

	ft_putendl_fd("building shaders...", 1);
	if (!(shader_src[0] = read_shader_file(vshader_path))
	|| !create_compile_shader(shader_src[0], &shader_ids[0], GL_VERTEX_SHADER))
		return (NULL);
	free(shader_src[0]);
	if (!(shader_src[1] = read_shader_file(fshader_path)) ||
	!create_compile_shader(shader_src[1], &shader_ids[1], GL_FRAGMENT_SHADER))
		return (NULL);
	free(shader_src[1]);
	if (!(this = (t_shader *)malloc(sizeof(t_shader))))
		return (NULL);
	if (!(create_link_program(&this->program_id, shader_ids[0], shader_ids[1])))
	{
		free(this);
		return (NULL);
	}
	glDeleteShader(shader_ids[0]);
	glDeleteShader(shader_ids[1]);
	init_shader(this);
	ft_putendl_fd("building shaders done.", 1);
	return (this);
}
