/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle_radian.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:34:51 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:34:55 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

double	ft_to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

double	ft_to_deg(double radian)
{
	return (radian * (180.0 / PI));
}

float	ft_to_radf(float deg)
{
	return (deg * ((float)PI / 180.0f));
}

float	ft_to_degf(float radian)
{
	return (radian * (180.0f / (float)PI));
}
