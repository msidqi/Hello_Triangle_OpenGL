/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:37:35 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:49:16 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** using row-major order // so we need to transpose the matrix for OpenGl
** https://en.wikipedia.org/wiki/Row-_and_column-major_order
*/

/*
** row type
*/

t_vec4			ft_mat4_x_vec4(t_mat4 m, t_vec4 v)
{
	return ((t_vec4){
	m.v[0][0] * v.x + m.v[0][1] * v.y + m.v[0][2] * v.z + m.v[0][3] * v.w,
	m.v[1][0] * v.x + m.v[1][1] * v.y + m.v[1][2] * v.z + m.v[1][3] * v.w,
	m.v[2][0] * v.x + m.v[2][1] * v.y + m.v[2][2] * v.z + m.v[2][3] * v.w,
	m.v[3][0] * v.x + m.v[3][1] * v.y + m.v[3][2] * v.z + m.v[3][3] * v.w
	});
}

/*
** for col type matrix ordering
*/

t_vec4			ft_mat4_x_vec4_col(t_mat4 m, t_vec4 v)
{
	return ((t_vec4){
	m.v[0][0] * v.x + m.v[1][0] * v.y + m.v[2][0] * v.z + m.v[3][0] * v.w,
	m.v[0][1] * v.x + m.v[1][1] * v.y + m.v[2][1] * v.z + m.v[3][1] * v.w,
	m.v[0][2] * v.x + m.v[1][2] * v.y + m.v[2][2] * v.z + m.v[3][2] * v.w,
	m.v[0][3] * v.x + m.v[1][3] * v.y + m.v[2][3] * v.z + m.v[3][3] * v.w
	});
}

/*
** row type
*/

t_mat4			ft_mat4_x_mat4(t_mat4 m0, t_mat4 m1)
{
	return ((t_mat4){
		.v = {
			{m0.v[0][0] * m1.v[0][0] + m0.v[0][1] * m1.v[1][0] + m0.v[0][2] * m1.v[2][0] + m0.v[0][3] * m1.v[3][0],
			m0.v[0][0] * m1.v[0][1] + m0.v[0][1] * m1.v[1][1] + m0.v[0][2] * m1.v[2][1] + m0.v[0][3] * m1.v[3][1],
			m0.v[0][0] * m1.v[0][2] + m0.v[0][1] * m1.v[1][2] + m0.v[0][2] * m1.v[2][2] + m0.v[0][3] * m1.v[3][2],
			m0.v[0][0] * m1.v[0][3] + m0.v[0][1] * m1.v[1][3] + m0.v[0][2] * m1.v[2][3] + m0.v[0][3] * m1.v[3][3]},

			{m0.v[1][0] * m1.v[0][0] + m0.v[1][1] * m1.v[1][0] + m0.v[1][2] * m1.v[2][0] + m0.v[1][3] * m1.v[3][0],
			m0.v[1][0] * m1.v[0][1] + m0.v[1][1] * m1.v[1][1] + m0.v[1][2] * m1.v[2][1] + m0.v[1][3] * m1.v[3][1],
			m0.v[1][0] * m1.v[0][2] + m0.v[1][1] * m1.v[1][2] + m0.v[1][2] * m1.v[2][2] + m0.v[1][3] * m1.v[3][2],
			m0.v[1][0] * m1.v[0][3] + m0.v[1][1] * m1.v[1][3] + m0.v[1][2] * m1.v[2][3] + m0.v[1][3] * m1.v[3][3]},

			{m0.v[2][0] * m1.v[0][0] + m0.v[2][1] * m1.v[1][0] + m0.v[2][2] * m1.v[2][0] + m0.v[2][3] * m1.v[3][0],
			m0.v[2][0] * m1.v[0][1] + m0.v[2][1] * m1.v[1][1] + m0.v[2][2] * m1.v[2][1] + m0.v[2][3] * m1.v[3][1],
			m0.v[2][0] * m1.v[0][2] + m0.v[2][1] * m1.v[1][2] + m0.v[2][2] * m1.v[2][2] + m0.v[2][3] * m1.v[3][2],
			m0.v[2][0] * m1.v[0][3] + m0.v[2][1] * m1.v[1][3] + m0.v[2][2] * m1.v[2][3] + m0.v[2][3] * m1.v[3][3]},

			{m0.v[3][0] * m1.v[0][0] + m0.v[3][1] * m1.v[1][0] + m0.v[3][2] * m1.v[2][0] + m0.v[3][3] * m1.v[3][0],
			m0.v[3][0] * m1.v[0][1] + m0.v[3][1] * m1.v[1][1] + m0.v[3][2] * m1.v[2][1] + m0.v[3][3] * m1.v[3][1],
			m0.v[3][0] * m1.v[0][2] + m0.v[3][1] * m1.v[1][2] + m0.v[3][2] * m1.v[2][2] + m0.v[3][3] * m1.v[3][2],
			m0.v[3][0] * m1.v[0][3] + m0.v[3][1] * m1.v[1][3] + m0.v[3][2] * m1.v[2][3] + m0.v[3][3] * m1.v[3][3]}
		}
	});
}

t_mat4			ft_mat4_x_mat4_col(t_mat4 m0, t_mat4 m1)
{
	return ((t_mat4){
		.v = {
			{m1.v[0][0] * m0.v[0][0] + m1.v[0][1] * m0.v[1][0] + m1.v[0][2] * m0.v[2][0] + m1.v[0][3] * m0.v[3][0],
			m1.v[0][0] * m0.v[0][1] + m1.v[0][1] * m0.v[1][1] + m1.v[0][2] * m0.v[2][1] + m1.v[0][3] * m0.v[3][1],
			m1.v[0][0] * m0.v[0][2] + m1.v[0][1] * m0.v[1][2] + m1.v[0][2] * m0.v[2][2] + m1.v[0][3] * m0.v[3][2],
			m1.v[0][0] * m0.v[0][3] + m1.v[0][1] * m0.v[1][3] + m1.v[0][2] * m0.v[2][3] + m1.v[0][3] * m0.v[3][3]},

			{m1.v[1][0] * m0.v[0][0] + m1.v[1][1] * m0.v[1][0] + m1.v[1][2] * m0.v[2][0] + m1.v[1][3] * m0.v[3][0],
			m1.v[1][0] * m0.v[0][1] + m1.v[1][1] * m0.v[1][1] + m1.v[1][2] * m0.v[2][1] + m1.v[1][3] * m0.v[3][1],
			m1.v[1][0] * m0.v[0][2] + m1.v[1][1] * m0.v[1][2] + m1.v[1][2] * m0.v[2][2] + m1.v[1][3] * m0.v[3][2],
			m1.v[1][0] * m0.v[0][3] + m1.v[1][1] * m0.v[1][3] + m1.v[1][2] * m0.v[2][3] + m1.v[1][3] * m0.v[3][3]},

			{m1.v[2][0] * m0.v[0][0] + m1.v[2][1] * m0.v[1][0] + m1.v[2][2] * m0.v[2][0] + m1.v[2][3] * m0.v[3][0],
			m1.v[2][0] * m0.v[0][1] + m1.v[2][1] * m0.v[1][1] + m1.v[2][2] * m0.v[2][1] + m1.v[2][3] * m0.v[3][1],
			m1.v[2][0] * m0.v[0][2] + m1.v[2][1] * m0.v[1][2] + m1.v[2][2] * m0.v[2][2] + m1.v[2][3] * m0.v[3][2],
			m1.v[2][0] * m0.v[0][3] + m1.v[2][1] * m0.v[1][3] + m1.v[2][2] * m0.v[2][3] + m1.v[2][3] * m0.v[3][3]},

			{m1.v[3][0] * m0.v[0][0] + m1.v[3][1] * m0.v[1][0] + m1.v[3][2] * m0.v[2][0] + m1.v[3][3] * m0.v[3][0],
			m1.v[3][0] * m0.v[0][1] + m1.v[3][1] * m0.v[1][1] + m1.v[3][2] * m0.v[2][1] + m1.v[3][3] * m0.v[3][1],
			m1.v[3][0] * m0.v[0][2] + m1.v[3][1] * m0.v[1][2] + m1.v[3][2] * m0.v[2][2] + m1.v[3][3] * m0.v[3][2],
			m1.v[3][0] * m0.v[0][3] + m1.v[3][1] * m0.v[1][3] + m1.v[3][2] * m0.v[2][3] + m1.v[3][3] * m0.v[3][3]}
		}
	});
}
