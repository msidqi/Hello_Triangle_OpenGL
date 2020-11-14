/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:35:25 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/14 11:39:03 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_vec4	ft_vec4_add(t_vec4 vec1, t_vec4 vec2)
{
	t_vec4 ret;

	ret.x = vec1.x + vec2.x;
	ret.y = vec1.y + vec2.y;
	ret.z = vec1.z + vec2.z;
	ret.w = 0;
	return (ret);
}

t_vec2	ft_vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2 ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return (ret);
}

t_vec3	ft_vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3 ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec3f	ft_vec3f_add(t_vec3f a, t_vec3f b)
{
	t_vec3f ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

void	ft_vec3f_add_a(t_vec3f *a, t_vec3f b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
}
