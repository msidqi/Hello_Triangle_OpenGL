/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 22:06:44 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/12 22:08:55 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shaders.h"

void set_int(struct s_shader *this, const char *name, int value)
{ 
    glUniform1i(glGetUniformLocation(this->program_id, name), value); 
}

void set_float(struct s_shader *this, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(this->program_id, name), value); 
}

void set_vec2(struct s_shader *this, const char *name, const t_vec2f *vec)
{ 
	glUniform2fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]);
}

void set_vec2f(struct s_shader *this, const char *name, float x, float y)
{ 
	glUniform2f(glGetUniformLocation(this->program_id, name), x, y); 
}

void set_vec3(struct s_shader *this, const char *name, const t_vec3f *vec)
{ 
	glUniform3fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}

void set_vec3f(struct s_shader *this, const char *name, float x, float y, float z)
{ 
	glUniform3f(glGetUniformLocation(this->program_id, name), x, y, z); 
}

static void set_vec4(struct s_shader *this, const char *name, const t_vec4f *vec)
{ 
	glUniform4fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}

static void set_vec4f(struct s_shader *this, const char *name, float x, float y, float z, float w)
{ 
	glUniform4f(glGetUniformLocation(this->program_id, name), x, y, z, w); 
}

static void	set_mat4f(struct s_shader *this, const char *name, const t_mat4f *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program_id, name), 1, GL_FALSE, (const GLfloat *)&mat->v);
}

void		init_shader(t_shader *this)
{
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
}
