/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouibr <aabouibr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:03:14 by msidqi            #+#    #+#             */
/*   Updated: 2019/12/31 19:25:41 by aabouibr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

void	ft_putvec3(t_vec3 *vec)
{
	write(1, "Vector( ", 9);
	ft_putnbr_fd(vec->x, 1);
	write(1, ", ", 3);
	ft_putnbr_fd(vec->y, 1);
	write(1, ", ", 3);
	ft_putnbr_fd(vec->z, 1);
	write(1, " )\n", 4);
}

void	ft_putvec4(t_vec4 *vec)
{
	write(1, "Vector( ", 9);
	ft_putnbr_fd(vec->x, 1);
	write(1, ", ", 3);
	ft_putnbr_fd(vec->y, 1);
	write(1, ", ", 3);
	ft_putnbr_fd(vec->z, 1);
	write(1, ", ", 3);
	ft_putnbr_fd(vec->w, 1);
	write(1, " )\n", 4);
}

void	ft_putmat4(t_mat4 *mat)
{
	int i;
	int j;

	i = -1;
	printf("Matrix( \n");
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			printf("% f", mat->v[i][j]);
			if (i < 3 || j < 3)
				printf(", ");
		}
		if (i < 3 || j < 3)
			printf("\n");
	}
	printf(" )\n");
}

void	ft_putmat4f(t_mat4f *mat)
{
	int i;
	int j;

	i = -1;
	printf("Matrix( \n");
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			printf("% f", mat->v[i][j]);
			if (i < 3 || j < 3)
				printf(", ");
		}
		if (i < 3 || j < 3)
			printf("\n");
	}
	printf(" )\n");
}
