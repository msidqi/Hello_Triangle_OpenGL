/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:18:55 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/22 20:42:06 by msidqi           ###   ########.fr       */
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

void	describe_buffer(GLuint location, GLint number_of_elements,
		GLenum gl_type, GLboolean normalized, GLsizei stride,
		GLuint index_in_stride, unsigned long type_size)
{
	glVertexAttribPointer(location, number_of_elements, gl_type, normalized,
			stride * type_size, (const void *)(index_in_stride * type_size));
	glEnableVertexAttribArray(location);
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
