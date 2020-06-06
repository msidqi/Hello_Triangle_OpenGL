/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transform_f.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 08:04:47 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 08:13:14 by msidqi           ###   ########.fr       */
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

/*
** rotation around X axis matrix
[1          0         0  ]
[0        cos(a)  -sin(a)]
[0        sin(a)   cos(a)]
*/

t_mat4f		ft_mat4f_rotation_x(float angle_rad)
{
	t_mat4f rotation;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_rad);
	sin_a = sinf(angle_rad);
	rotation = ft_mat4f_create();
	rotation.v[1][1] = cos_a;
	rotation.v[2][2] = cos_a;
	rotation.v[1][2] = -sin_a;
	rotation.v[2][1] = sin_a;
	return (rotation);
}

/*
** rotation around Y axis matrix
[cos(a)     0      sin(a)]
[0          1         0  ]
[-sin(a)    0      cos(a)]
*/

t_mat4f		ft_mat4f_rotation_y(float angle_rad)
{
	t_mat4f rotation;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_rad);
	sin_a = sinf(angle_rad);
	rotation = ft_mat4f_create();
	rotation.v[0][0] = cos_a;
	rotation.v[2][2] = cos_a;
	rotation.v[0][2] = -sin_a;
	rotation.v[2][0] = sin_a;
	return (rotation);
}

/*
** rotation around Z axis matrix
[cos(a)  -sin(a)      0  ]
[sin(a)   cos(a)      0  ]
[  0        0         0  ]
*/

t_mat4f		ft_mat4f_rotation_z(float angle_rad)
{
	t_mat4f rotation;
	float cos_a;
	float sin_a;

	cos_a = cosf(angle_rad);
	sin_a = sinf(angle_rad);
	rotation = ft_mat4f_create();
	rotation.v[0][0] = cos_a;
	rotation.v[1][1] = cos_a;
	rotation.v[2][2] = 0;
	rotation.v[0][1] = sin_a;
	rotation.v[1][0] = -sin_a;

	return (rotation);
}

t_mat4f		ft_mat4f_rotation_xyz(float angle_rad, t_vec3f v)
{
	return (ft_mat4f_x_mat4f(
		ft_mat4f_rotation_x(angle_rad * v.x),
		ft_mat4f_x_mat4f(ft_mat4f_rotation_y(angle_rad * v.y),
						ft_mat4f_rotation_z(angle_rad * v.z))));
}

t_mat4f		ft_mat4f_rotate(t_mat4f mat, float angle_rad, t_vec3f v)
{
	t_mat4f rotation;

	rotation = ft_mat4f_rotation_xyz(angle_rad, v);
	return (ft_mat4f_x_mat4f(mat, rotation));
}

