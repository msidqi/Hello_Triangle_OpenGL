/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_perspective.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 08:20:49 by msidqi           ###   ########.fr       */
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
	perspective.v[2][3] = 2.0f * far * near / (near - far);
	perspective.v[3][2] = 1.0f;
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
	perspective.v[2][3] = 2.0f * far * near / (near - far);
	perspective.v[3][2] = 1.0f;
	return (perspective);
}

/*t_mat4	ft_perspective_matrixr(float fov_rad, float asp_ratio, float near, float far)
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
	perspective.v[2][3] = 2.0f * far * near / (near - far);
	perspective.v[3][2] = 1.0f;
	return (perspective);
}

template<typename T>
	GLM_FUNC_QUALIFIER mat<4, 4, T, defaultp> perspectiveRH_ZO(T fovy, T aspect, T zNear, T zFar)
	{
		assert(abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

		T const tanHalfFovy = tan(fovy / 2.0f);

		mat<4, 4, T, defaultp> Result(static_cast<T>(0));
		Result[0][0] = 1.0f / (aspect * tanHalfFovy);
		Result[1][1] = 1.0f / (tanHalfFovy);
		Result[2][2] = zFar / (zNear - zFar);
		Result[2][3] = - 1.0f;
		Result[3][2] = -(zFar * zNear) / (zFar - zNear);
		return Result;
	}
*/