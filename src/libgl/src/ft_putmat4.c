/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 11:22:56 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 11:23:20 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

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
