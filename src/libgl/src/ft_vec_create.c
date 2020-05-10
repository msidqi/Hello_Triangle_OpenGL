/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2019/10/05 15:37:52 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void		ft_create_vec2(t_vec2 *a, double x, double y)
{
	a->x = x;
	a->y = y;
}

void		ft_create_vec3(t_vec3 *a, double x, double y, double z)
{
	a->x = x;
	a->y = y;
	a->z = z;
}

t_vec4		ft_create_vec4(double x, double y, double z, double w)
{
	t_vec4	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}
