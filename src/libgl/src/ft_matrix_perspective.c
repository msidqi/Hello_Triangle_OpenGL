/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_perspective.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 18:03:40 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
//perspective(radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);

t_mat4	ft_perspective_matrix(float fov_rad, float asp_ratio, float near, float far)
{
	t_mat4	perspective;
	float	tan_fov_over_2;
	
	tan_fov_over_2 = tanf(fov_rad / 2.0f);
	if (near < 0.0f)
		near = 0.1f;
	if (far < 0.0f)
		far = 100.0f;
	perspective = ft_mat4_create();
	perspective.v[0][0] = 1.0f / (tan_fov_over_2 * asp_ratio);
	perspective.v[1][1] = 1.0f / tan_fov_over_2;
	perspective.v[2][2] = (-near - far) / (near - far);
	perspective.v[2][3] = 1.0f;
	perspective.v[3][2] = 2.0f * far * near / (near - far);
	return (perspective);
}

t_mat4f	ft_perspective_matrixf(float fov_rad, float asp_ratio, float near, float far)
{
	t_mat4f	perspective;
	float	tan_fov_over_2;
	
	tan_fov_over_2 = tanf(fov_rad / 2.0f);
	if (near < 0.0f)
		near = 0.1f;
	if (far < 0.0f)
		far = 100.0f;
	perspective = ft_mat4f_create();
	perspective.v[0][0] = 1.0f / (tan_fov_over_2 * asp_ratio);
	perspective.v[1][1] = 1.0f / tan_fov_over_2;
	perspective.v[2][2] = (-near - far) / (near - far);
	perspective.v[2][3] = 1.0f;
	perspective.v[3][2] = 2.0f * far * near / (near - far);
	return (perspective);
}

t_mat4f	ft_perspective_matrixf_row(float fov_rad, float asp_ratio, float near, float far)
{
	t_mat4f	perspective;
	float	tan_fov_over_2;
	
	tan_fov_over_2 = tanf(fov_rad / 2.0f);
	if (near < 0.0f)
		near = 0.1f;
	if (far < 0.0f)
		far = 100.0f;
	perspective = ft_mat4f_create();
	perspective.v[0][0] = 1.0f / (tan_fov_over_2 * asp_ratio);
	perspective.v[1][1] = 1.0f / tan_fov_over_2;
	perspective.v[2][2] = (-near - far) / (near - far);
	perspective.v[2][3] = 2.0f * far * near / (near - far);
	perspective.v[3][2] = 1.0f;
	return (perspective);
}
