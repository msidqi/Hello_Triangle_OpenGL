/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_key_press.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:37:17 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/14 20:30:46 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	ft_handle_key_press(t_event_handler *e, int key)
{
	if (key == GLFW_KEY_S)
		e->is_scale_mode = !e->is_scale_mode;
	if (key == GLFW_KEY_R)
		e->is_rot_mode = !e->is_rot_mode;
	if (key == GLFW_KEY_T)
		e->is_smooth_transition = !e->is_smooth_transition;
	if (key == GLFW_KEY_N)
	{
		e->is_smooth_noise_transition = !e->is_smooth_noise_transition;
		e->noise_coef = 0;
		e->is_shading = 0;
	}
	if (key == GLFW_KEY_Y)
	{
		e->is_shading = !e->is_shading;
		e->noise_coef = 0;
	}
	if (key == GLFW_KEY_1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (key == GLFW_KEY_2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (key == GLFW_KEY_3)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}
