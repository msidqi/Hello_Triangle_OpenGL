/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_create_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:33:45 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:43:12 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

/*
**				@DEPRECATED
**
** free matrix with ft_destroy_matrix
*/

t_matrix	*ft_create_matrix(int rows, int cols)
{
	t_matrix		*mat;
	int				i;
	int				j;

	i = -1;
	if (rows != cols || rows * cols < 2 || !(mat = malloc(sizeof(t_matrix))))
		return (NULL);
	if (!(mat->v = (double **)malloc(sizeof(double*) * rows)))
		return (NULL);
	mat->cols = cols;
	mat->rows = rows;
	while (++i < rows)
	{
		mat->v[i] = (double *)malloc(sizeof(double) * cols);
		j = -1;
		while (++j < cols)
		{
			if (j == i)
				mat->v[i][j] = 1;
			else
				mat->v[i][j] = 0;
		}
	}
	return (mat);
}

t_mat4		ft_create_matrix4(void)
{
	unsigned int	i;
	unsigned int	j;
	t_mat4			mat;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == i)
				mat.v[i][j] = 1;
			else
				mat.v[i][j] = 0;
		}
	}
	return (mat);
}

int			ft_destroy_matrix(t_matrix *mat)
{
	int	i;

	i = -1;
	if (!mat)
		return (0);
	while (++i < mat->rows)
		free(mat->v[i]);
	free(mat->v);
	free(mat);
	return (1);
}
