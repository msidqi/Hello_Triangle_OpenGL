/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:18:55 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 18:44:56 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** stride == total_num_of_elements =>
** [|v0, v1, v2,| |v3, v4|]
** [|vertexdata | |colors|]
** number_of_elements equals 3 for vertexdata and 2 for colors
**
** index_in_stride is the starting point =>
** 		0 (v0) for vertexdata and 3 (v3) for colors
*/

void	describe_buffer(t_bp params)
{
	glVertexAttribPointer(params.location, params.number_of_elements,
		params.gl_type, params.normalized,
		params.stride * params.type_size,
		(const void *)(params.index_in_stride * params.type_size));
	glEnableVertexAttribArray(params.location);
}

void	generate_buffer(unsigned int *vbo)
{
	glGenBuffers(1, vbo);
}

void	bind_buffer(GLuint target_buffer, GLuint buffer,
		unsigned long buffer_size, const void *data)
{
	glBindBuffer(target_buffer, buffer);
	glBufferData(target_buffer, buffer_size, data, GL_STATIC_DRAW);
}

void	generate_vao(GLuint *vao)
{
	glGenVertexArrays(1, vao);
}

void	bind_vao(GLuint vao)
{
	glBindVertexArray(vao);
}
