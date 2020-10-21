/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transform2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/21 18:00:00 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
** rotation around X axis matrix
** [1          0         0  ]
** [0        cos(a)  -sin(a)]
** [0        sin(a)   cos(a)]
*/

t_mat4		ft_mat4_rotation_x(double angle_rad)
{
	t_mat4 rotation;
	double cos_a;
	double sin_a;

	cos_a = cos(angle_rad);
	sin_a = sin(angle_rad);
	rotation = ft_mat4_create();
	rotation.v[1][1] = cos_a;
	rotation.v[2][2] = cos_a;
	rotation.v[1][2] = -sin_a;
	rotation.v[2][1] = sin_a;
	return (rotation);
}

/*
** rotation around Y axis matrix
** [cos(a)     0      sin(a)]
** [0          1         0  ]
** [-sin(a)    0      cos(a)]
*/

t_mat4		ft_mat4_rotation_y(double angle_rad)
{
	t_mat4 rotation;
	double cos_a;
	double sin_a;

	cos_a = cos(angle_rad);
	sin_a = sin(angle_rad);
	rotation = ft_mat4_create();
	rotation.v[0][0] = cos_a;
	rotation.v[2][2] = cos_a;
	rotation.v[0][2] = -sin_a;
	rotation.v[2][0] = sin_a;
	return (rotation);
}

/*
** rotation around Z axis matrix
** [cos(a)  -sin(a)      0  ]
** [sin(a)   cos(a)      0  ]
** [  0        0         0  ]
*/

t_mat4		ft_mat4_rotation_z(double angle_rad)
{
	t_mat4 rotation;
	double cos_a;
	double sin_a;

	cos_a = cos(angle_rad);
	sin_a = sin(angle_rad);
	rotation = ft_mat4_create();
	rotation.v[0][0] = cos_a;
	rotation.v[1][1] = cos_a;
	rotation.v[2][2] = 0;
	rotation.v[0][1] = sin_a;
	rotation.v[1][0] = -sin_a;
	return (rotation);
}

t_mat4		ft_mat4_rotation_xyz(double angle_rad, t_vec3 v)
{
	return (ft_mat4_x_mat4(
		ft_mat4_rotation_x(angle_rad * v.x),
		ft_mat4_x_mat4(ft_mat4_rotation_y(angle_rad * v.y),
						ft_mat4_rotation_z(angle_rad * v.z))));
}

t_mat4		ft_mat4_rotate(t_mat4 mat, double angle_rad, t_vec3 v)
{
	t_mat4 rotation;

	rotation = ft_mat4_rotation_xyz(angle_rad, v);
	return (ft_mat4_x_mat4(mat, rotation));
}
