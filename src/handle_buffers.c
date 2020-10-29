/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_buffers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:38:36 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 18:38:39 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	handle_buffers(t_env *env)
{
	t_obj *obj;

	obj = env->obj;
	generate_buffer(&env->vbo);
	generate_vao(&env->vao);
	generate_buffer(&env->ebo);
	if (obj->flags & F_INDEX && obj->flags & F_TEXTURE_INDEX)
	{
		bind_vao(env->vao);
		bind_buffer(GL_ARRAY_BUFFER, env->vbo,
		sizeof(float) * obj->vertices_len * 5, obj->vertices_array);
		bind_buffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo,
		sizeof(unsigned int) * obj->indices_len * 3, obj->vindices_array);
		describe_buffer((t_bp){0, 3, GL_FLOAT, GL_FALSE, 5, 0, sizeof(float)});
		describe_buffer((t_bp){1, 2, GL_FLOAT, GL_FALSE, 5, 3, sizeof(float)});
	}
	else
	{
		bind_vao(env->vao);
		bind_buffer(GL_ARRAY_BUFFER, env->vbo,
		sizeof(float) * obj->vertices_len * 3, obj->vertices_array);
		bind_buffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo,
		sizeof(unsigned int) * obj->indices_len * 3, obj->vindices_array);
		describe_buffer((t_bp){0, 3, GL_FLOAT, GL_FALSE, 3, 0, sizeof(float)});
	}
}
