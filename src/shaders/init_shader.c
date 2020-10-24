/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 22:06:44 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/24 16:26:37 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shaders.h"

void	init_shader(t_shader *this)
{
	this->use = &use_shader_program;
	this->set_int = &set_int;
	this->set_float = &set_float;
	this->set_vec2 = &set_vec2;
	this->set_vec2f = &set_vec2f;
	this->set_vec3 = &set_vec3;
	this->set_vec4 = &set_vec4;
	this->set_mat4f = &set_mat4f;
}
