/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:03:14 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 11:22:39 by msidqi           ###   ########.fr       */
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
