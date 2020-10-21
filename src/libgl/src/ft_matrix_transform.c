/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transform.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/21 17:36:06 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_mat4		ft_mat4_scale_d(t_mat4 mat, double x, double y,
		double z)
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_mat4		ft_mat4_scale(t_mat4 mat, t_vec3 v)
{
	mat.v[0][0] *= v.x;
	mat.v[1][1] *= v.y;
	mat.v[2][2] *= v.z;
	return (mat);
}

t_mat4		ft_mat4_translate_d(t_mat4 mat, double x, double y, double z)
{
	mat.v[0][3] += x;
	mat.v[1][3] += y;
	mat.v[2][3] += z;
	return (mat);
}

t_mat4		ft_mat4_translate(t_mat4 mat, t_vec3 v)
{
	mat.v[3][0] += v.x;
	mat.v[3][1] += v.y;
	mat.v[3][2] += v.z;
	return (mat);
}

t_mat4		ft_mat4_translate_row(t_mat4 mat, t_vec3 v)
{
	mat.v[0][3] += v.x;
	mat.v[1][3] += v.y;
	mat.v[2][3] += v.z;
	return (mat);
}
