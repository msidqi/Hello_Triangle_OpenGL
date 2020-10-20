/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:51:58 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:36:03 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_mat4		ft_get_translation_matrix4(t_mat4 mat, double x, double y,
		double z)
{
	mat.v[0][3] += x;
	mat.v[1][3] += y;
	mat.v[2][3] += z;
	return (mat);
}

/*
** pass identity matrix in mat for default value
*/

t_mat4		ft_get_scaling_matrix4(t_mat4 mat, double x, double y,
		double z)
{
	mat.v[0][0] *= x;
	mat.v[1][1] *= y;
	mat.v[2][2] *= z;
	return (mat);
}

t_vec4		ft_translate_vec4(t_vec4 vec, double x, double y, double z)
{
	t_mat4 tr_mat;

	tr_mat = ft_mat4_create();
	tr_mat.v[0][3] += x;
	tr_mat.v[1][3] += y;
	tr_mat.v[2][3] += z;
	return (ft_mat4_x_vec4(tr_mat, vec));
}
