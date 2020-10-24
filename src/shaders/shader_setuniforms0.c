/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_setuniforms0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 16:25:47 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/24 16:26:12 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shaders.h"

void	set_vec2(struct s_shader *this, const char *name, const t_vec2f *vec)
{ 
	glUniform2fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]);
}

void	set_vec2f(struct s_shader *this, const char *name, float x, float y)
{ 
	glUniform2f(glGetUniformLocation(this->program_id, name), x, y); 
}

void	set_vec3(struct s_shader *this, const char *name, const t_vec3f *vec)
{ 
	glUniform3fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}

void	set_vec4(struct s_shader *this, const char *name, const t_vec4f *vec)
{ 
	glUniform4fv(glGetUniformLocation(this->program_id, name), 1, (const float *)&vec[0]); 
}
