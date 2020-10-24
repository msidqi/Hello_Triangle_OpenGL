/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_setuniforms1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:25:54 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/24 16:26:23 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shaders.h"

void	set_int(struct s_shader *this, const char *name, int value)
{ 
    glUniform1i(glGetUniformLocation(this->program_id, name), value); 
}

void	set_float(struct s_shader *this, const char *name, float value)
{
    glUniform1f(glGetUniformLocation(this->program_id, name), value); 
}

void	set_mat4f(struct s_shader *this, const char *name, const t_mat4f *mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program_id, name), 1, GL_FALSE, (const GLfloat *)&mat->v);
}