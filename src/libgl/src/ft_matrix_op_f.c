/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_op_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 08:05:28 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 18:06:09 by msidqi           ###   ########.fr       */
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

t_vec4f			ft_mat4f_x_vec4f(t_mat4f m, t_vec4f v)
{
	return ((t_vec4f){
	m.v[0][0] * v.x + m.v[0][1] * v.y + m.v[0][2] * v.z + m.v[0][3] * v.w,
	m.v[1][0] * v.x + m.v[1][1] * v.y + m.v[1][2] * v.z + m.v[1][3] * v.w,
	m.v[2][0] * v.x + m.v[2][1] * v.y + m.v[2][2] * v.z + m.v[2][3] * v.w,
	m.v[3][0] * v.x + m.v[3][1] * v.y + m.v[3][2] * v.z + m.v[3][3] * v.w
	});
}

/*
** for col type matrix ordering
*/

t_vec4f			ft_mat4f_x_vec4f_col(t_mat4f m, t_vec4f v)
{
	return ((t_vec4f){
	m.v[0][0] * v.x + m.v[1][0] * v.y + m.v[2][0] * v.z + m.v[3][0] * v.w,
	m.v[0][1] * v.x + m.v[1][1] * v.y + m.v[2][1] * v.z + m.v[3][1] * v.w,
	m.v[0][2] * v.x + m.v[1][2] * v.y + m.v[2][2] * v.z + m.v[3][2] * v.w,
	m.v[0][3] * v.x + m.v[1][3] * v.y + m.v[2][3] * v.z + m.v[3][3] * v.w
	});
}

/*
** row type
*/

t_mat4f			ft_mat4f_x_mat4f(t_mat4f m, t_mat4f n)
{
	return ((t_mat4f){
.v = {
	{m.v[0][0] * n.v[0][0] + m.v[0][1] * n.v[1][0] + m.v[0][2] * n.v[2][0] +
	m.v[0][3] * n.v[3][0], m.v[0][0] * n.v[0][1] + m.v[0][1] * n.v[1][1] +
	m.v[0][2] * n.v[2][1] + m.v[0][3] * n.v[3][1], m.v[0][0] * n.v[0][2] +
	m.v[0][1] * n.v[1][2] + m.v[0][2] * n.v[2][2] + m.v[0][3] * n.v[3][2],
	m.v[0][0] * n.v[0][3] + m.v[0][1] * n.v[1][3] + m.v[0][2] * n.v[2][3] +
	m.v[0][3] * n.v[3][3]}, {m.v[1][0] * n.v[0][0] + m.v[1][1] * n.v[1][0] +
	m.v[1][2] * n.v[2][0] + m.v[1][3] * n.v[3][0], m.v[1][0] * n.v[0][1] +
	m.v[1][1] * n.v[1][1] + m.v[1][2] * n.v[2][1] + m.v[1][3] * n.v[3][1],
	m.v[1][0] * n.v[0][2] + m.v[1][1] * n.v[1][2] + m.v[1][2] * n.v[2][2]
	+ m.v[1][3] * n.v[3][2], m.v[1][0] * n.v[0][3] + m.v[1][1] * n.v[1][3]
	+ m.v[1][2] * n.v[2][3] + m.v[1][3] * n.v[3][3]}, {m.v[2][0] * n.v[0][0]
	+ m.v[2][1] * n.v[1][0] + m.v[2][2] * n.v[2][0] + m.v[2][3] * n.v[3][0],
	m.v[2][0] * n.v[0][1] + m.v[2][1] * n.v[1][1] + m.v[2][2] * n.v[2][1] +
	m.v[2][3] * n.v[3][1], m.v[2][0] * n.v[0][2] + m.v[2][1] * n.v[1][2] +
	m.v[2][2] * n.v[2][2] + m.v[2][3] * n.v[3][2], m.v[2][0] * n.v[0][3] +
	m.v[2][1] * n.v[1][3] + m.v[2][2] * n.v[2][3] + m.v[2][3] * n.v[3][3]},
	{m.v[3][0] * n.v[0][0] + m.v[3][1] * n.v[1][0] + m.v[3][2] * n.v[2][0] +
	m.v[3][3] * n.v[3][0], m.v[3][0] * n.v[0][1] + m.v[3][1] * n.v[1][1] +
	m.v[3][2] * n.v[2][1] + m.v[3][3] * n.v[3][1], m.v[3][0] * n.v[0][2] +
	m.v[3][1] * n.v[1][2] + m.v[3][2] * n.v[2][2] + m.v[3][3] * n.v[3][2],
	m.v[3][0] * n.v[0][3] + m.v[3][1] * n.v[1][3] + m.v[3][2] * n.v[2][3] +
	m.v[3][3] * n.v[3][3]}}
	});
}

t_mat4f			ft_mat4f_x_mat4f_col(t_mat4f m, t_mat4f n)
{
	return ((t_mat4f){
.v = {
	{n.v[0][0] * m.v[0][0] + n.v[0][1] * m.v[1][0] + n.v[0][2] * m.v[2][0] +
	n.v[0][3] * m.v[3][0], n.v[0][0] * m.v[0][1] + n.v[0][1] * m.v[1][1] +
	n.v[0][2] * m.v[2][1] + n.v[0][3] * m.v[3][1], n.v[0][0] * m.v[0][2] +
	n.v[0][1] * m.v[1][2] + n.v[0][2] * m.v[2][2] + n.v[0][3] * m.v[3][2],
	n.v[0][0] * m.v[0][3] + n.v[0][1] * m.v[1][3] + n.v[0][2] * m.v[2][3] +
	n.v[0][3] * m.v[3][3]}, {n.v[1][0] * m.v[0][0] + n.v[1][1] * m.v[1][0] +
	n.v[1][2] * m.v[2][0] + n.v[1][3] * m.v[3][0], n.v[1][0] * m.v[0][1] +
	n.v[1][1] * m.v[1][1] + n.v[1][2] * m.v[2][1] + n.v[1][3] * m.v[3][1],
	n.v[1][0] * m.v[0][2] + n.v[1][1] * m.v[1][2] + n.v[1][2] * m.v[2][2] +
	n.v[1][3] * m.v[3][2], n.v[1][0] * m.v[0][3] + n.v[1][1] * m.v[1][3] +
	n.v[1][2] * m.v[2][3] + n.v[1][3] * m.v[3][3]}, {n.v[2][0] * m.v[0][0]
	+ n.v[2][1] * m.v[1][0] + n.v[2][2] * m.v[2][0] + n.v[2][3] * m.v[3][0],
	n.v[2][0] * m.v[0][1] + n.v[2][1] * m.v[1][1] + n.v[2][2] * m.v[2][1] +
	n.v[2][3] * m.v[3][1], n.v[2][0] * m.v[0][2] + n.v[2][1] * m.v[1][2] +
	n.v[2][2] * m.v[2][2] + n.v[2][3] * m.v[3][2], n.v[2][0] * m.v[0][3] +
	n.v[2][1] * m.v[1][3] + n.v[2][2] * m.v[2][3] + n.v[2][3] * m.v[3][3]},
	{n.v[3][0] * m.v[0][0] + n.v[3][1] * m.v[1][0] + n.v[3][2] * m.v[2][0] +
	n.v[3][3] * m.v[3][0], n.v[3][0] * m.v[0][1] + n.v[3][1] * m.v[1][1] +
	n.v[3][2] * m.v[2][1] + n.v[3][3] * m.v[3][1], n.v[3][0] * m.v[0][2] +
	n.v[3][1] * m.v[1][2] + n.v[3][2] * m.v[2][2] + n.v[3][3] * m.v[3][2],
	n.v[3][0] * m.v[0][3] + n.v[3][1] * m.v[1][3] + n.v[3][2] * m.v[2][3] +
	n.v[3][3] * m.v[3][3]}}
	});
}
