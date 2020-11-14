/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_callbacks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:37:17 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/14 19:44:18 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	t_event_handler *e;

	e = get_event_handler();
	if (e->is_right_click)
	{
		if (yoffset > 0)
			e->rotation.z += .05f;
		if (yoffset < 0)
			e->rotation.z -= .05f;
		e->is_scale_mode = 0;
	}
	else if (e->is_scale_mode)
	{
		if (yoffset > 0)
			e->scale_factor += 0.1f;
		if (yoffset < 0)
			e->scale_factor -= 0.1f;
	}
	else
	{
		if (yoffset > 0)
			e->translation.z += .3f * e->translation_mod;
		if (yoffset < 0)
			e->translation.z -= .3f * e->translation_mod;
	}
}

void	cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	t_event_handler *e;

	e = get_event_handler();
	e->rel_mouse_xpos = xpos - e->mouse_xpos_old;
	e->rel_mouse_ypos = ypos - e->mouse_ypos_old;
	if (e->is_left_click)
	{
		e->translation.y += e->translation_mod * .003f * -e->rel_mouse_ypos;
		e->translation.x += e->translation_mod * .003f * e->rel_mouse_xpos;
	}
	if (e->is_right_click)
	{
		e->rotation.y += .005f * e->rel_mouse_xpos;
		e->rotation.x += .005f * e->rel_mouse_ypos;
	}
	e->mouse_xpos_old = xpos;
	e->mouse_ypos_old = ypos;
}

void	mouse_button_callback(GLFWwindow *window,
							int button, int action, int mods)
{
	t_event_handler *e;

	e = get_event_handler();
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		e->is_left_click = 1;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		e->is_left_click = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		e->is_right_click = 1;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		e->is_right_click = 0;
}

void	key_callback(GLFWwindow *window,
							int key, int scancode, int action, int mods)
{
	t_event_handler *e;

	e = get_event_handler();
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		else
			ft_handle_key_press(e, key);
	}
}

/*
** callback to resize the viewport @ window size-change
*/

void	framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	t_event_handler *e;

	e = get_event_handler();
	e->height = height;
	e->width = width;
	glViewport(0, 0, width, height);
}
