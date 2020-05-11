/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/04/23 15:37:52 by msidqi           ###   ########.fr       */
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
[cos(a)     0      sin(a)]
[0          1         0  ]
[-sin(a)    0      cos(a)]
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
[cos(a)  -sin(a)      0  ]
[sin(a)   cos(a)      0  ]
[  0        0         0  ]
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
		ft_mat4_x_mat4(ft_mat4_rotation_x(angle_rad * v.y),
						ft_mat4_rotation_z(angle_rad * v.z))));
}

t_mat4		ft_mat4_rotate(t_mat4 mat, double angle_rad, t_vec3 v)
{
	t_mat4 rotation;

	rotation = ft_mat4_rotation_xyz(angle_rad, v);
	return (ft_mat4_x_mat4(mat, rotation));
}


/*
 @deprecated
*/

/*t_mat4		ft_mat4_rotate(t_mat4 mat, double angle_rad, t_vec3 v)
{
	double cos_a = cos(angle_rad);
	double sin_a = sin(angle_rad);

	t_vec3 axis = ft_vec3_normalize(v);

	t_vec3 temp = ft_vec3_scalar(axis, 1.0 - cos_a);

	t_mat4 identity = ft_mat4_create();
	
	t_mat4 rotate = identity;
	rotate.v[0][0] = cos_a + temp.x * axis.x;
	rotate.v[0][1] = 0 +     temp.x * axis.y + sin_a * axis.z;
	rotate.v[0][2] = 0 +     temp.x * axis.z - sin_a * axis.y;

	rotate.v[1][0] = 0 +     temp.y * axis.x - sin_a * axis.z;
	rotate.v[1][1] = cos_a + temp.y * axis.y;
	rotate.v[1][2] = 0 +     temp.y * axis.z + sin_a * axis.x;

	rotate.v[2][0] = 0 +     temp.z * axis.x + sin_a * axis.y;
	rotate.v[2][1] = 0 +     temp.z * axis.y - sin_a * axis.x;
	rotate.v[2][2] = cos_a + temp.z * axis.z;

	t_mat4 result = identity;
	result.v[0][0] = mat.v[0][0] * rotate.v[0][0] + mat.v[1][1] * rotate.v[0][1] + mat.v[2][2] * rotate.v[0][2];
	result.v[1][1] = mat.v[0][0] * rotate.v[1][0] + mat.v[1][1] * rotate.v[1][1] + mat.v[2][2] * rotate.v[1][2];
	result.v[2][2] = mat.v[0][0] * rotate.v[2][0] + mat.v[1][1] * rotate.v[2][1] + mat.v[2][2] * rotate.v[2][2];
	result.v[3][3] = mat.v[3][3];
	return result;
}*/
