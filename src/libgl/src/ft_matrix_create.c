/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:31:41 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 08:19:47 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

t_mat4	ft_mat4_create(void)
{
	unsigned int	i;
	unsigned int	j;
	t_mat4		mat;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == i)
				mat.v[i][j] = 1.0;
			else
				mat.v[i][j] = 0.0;
		}
	}
	return (mat);
}

t_mat4	ft_mat4_create_init(double init)
{
	t_mat4 mat;

	mat.v[0][0] = init;
	mat.v[0][1] = 0;
	mat.v[0][2] = 0;
	mat.v[0][3] = 0;

	mat.v[1][0] = 0;
	mat.v[1][1] = init;
	mat.v[1][2] = 0;
	mat.v[1][3] = 0;

	mat.v[2][0] = 0;
	mat.v[2][1] = 0;
	mat.v[2][2] = init;
	mat.v[2][3] = 0;

	mat.v[3][0] = 0;
	mat.v[3][1] = 0;
	mat.v[3][2] = 0;
	mat.v[3][3] = 1;
	return (mat);
}

t_mat4f	ft_mat4f_create(void)
{
	unsigned int	i;
	unsigned int	j;
	t_mat4f			mat;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == i)
				mat.v[i][j] = 1.0;
			else
				mat.v[i][j] = 0.0;
		}
	}
	return (mat);
}

t_mat4f	ft_mat4f_create_init(float init)
{
	t_mat4f mat;

	mat.v[0][0] = init;
	mat.v[0][1] = 0;
	mat.v[0][2] = 0;
	mat.v[0][3] = 0;

	mat.v[1][0] = 0;
	mat.v[1][1] = init;
	mat.v[1][2] = 0;
	mat.v[1][3] = 0;

	mat.v[2][0] = 0;
	mat.v[2][1] = 0;
	mat.v[2][2] = init;
	mat.v[2][3] = 0;

	mat.v[3][0] = 0;
	mat.v[3][1] = 0;
	mat.v[3][2] = 0;
	mat.v[3][3] = 1;
	return (mat);
}
