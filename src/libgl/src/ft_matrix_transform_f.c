/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transform_f.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 08:04:47 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/21 18:00:28 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_mat4f		ft_mat4f_scale_f(t_mat4f mat, float x, float y,
		float z)
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_mat4f		ft_mat4f_scale(t_mat4f mat, t_vec3f v)
{
	mat.v[0][0] *= v.x;
	mat.v[1][1] *= v.y;
	mat.v[2][2] *= v.z;
	return (mat);
}

t_mat4f		ft_mat4f_translate_f(t_mat4f mat, float x, float y, float z)
{
	mat.v[0][3] += x;
	mat.v[1][3] += y;
	mat.v[2][3] += z;
	return (mat);
}

t_mat4f		ft_mat4f_translate(t_mat4f mat, t_vec3f v)
{
	mat.v[3][0] += v.x;
	mat.v[3][1] += v.y;
	mat.v[3][2] += v.z;
	return (mat);
}

t_mat4f		ft_mat4f_translate_row(t_mat4f mat, t_vec3f v)
{
	mat.v[0][3] += v.x;
	mat.v[1][3] += v.y;
	mat.v[2][3] += v.z;
	return (mat);
}
