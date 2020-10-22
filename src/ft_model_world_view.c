/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_model_world_view.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 20:21:05 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/22 20:21:12 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void		ft_model_world_view(t_event_handler *e, t_mat4f *result)
{
	t_mat4f identity;
	t_mat4f model;
	t_mat4f view;
	t_mat4f projection;

	identity = ft_mat4f_create_init(e->scale_factor);
	model = ft_mat4f_rotation_xyz(ft_to_radf(e->rot_angle), e->rotation);
	view = ft_mat4f_translate(identity, e->translation);
	projection = ft_perspective_matrixf(ft_to_radf(45.0f),
				(float)((float)e->width / (float)e->height), 0.1f, 100.0f);
	(*result) = ft_mat4f_x_mat4f(model, ft_mat4f_x_mat4f(view, projection));
}
