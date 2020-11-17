/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:37:17 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/17 20:37:23 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_event_handler	g_e;

t_event_handler	*get_event_handler(void)
{
	return (&g_e);
}

static void		input_smooth_transition(t_event_handler *e_handler)
{
	static int dir = 1;

	if (e_handler->initial_trans_time == .0f)
		e_handler->initial_trans_time = (float)glfwGetTime();
	if (dir == 1)
		e_handler->mix_value +=
		((float)glfwGetTime() - e_handler->initial_trans_time) / 100.0f;
	else if (dir == -1)
		e_handler->mix_value -=
		((float)glfwGetTime() - e_handler->initial_trans_time) / 100.0f;
	if (e_handler->mix_value > 1.0f)
	{
		dir = -1;
		e_handler->mix_value = 1.0f;
		e_handler->is_smooth_transition = 0;
		e_handler->initial_trans_time = .0f;
	}
	else if (e_handler->mix_value < .0f)
	{
		dir = 1;
		e_handler->mix_value = .0f;
		e_handler->is_smooth_transition = 0;
		e_handler->initial_trans_time = .0f;
	}
}

static void		smooth_noise_transition(t_event_handler *e_handler)
{
	if (e_handler->initial_trans_time == .0f)
		e_handler->initial_trans_time = (float)glfwGetTime();
	if (e_handler->is_smooth_noise_transition == 1)
		e_handler->noise_coef +=
		((float)glfwGetTime() - e_handler->initial_trans_time) / 10.0f;
	if (e_handler->is_smooth_noise_transition == -1)
		e_handler->noise_coef -=
		((float)glfwGetTime() - e_handler->initial_trans_time) / 10.0f;
	if (e_handler->noise_coef >= 100.0f)
		e_handler->is_smooth_noise_transition = -1;
	if (e_handler->noise_coef < 2.0f)
		e_handler->initial_trans_time = (float)glfwGetTime();
	if (e_handler->noise_coef < 1.0f)
		e_handler->is_smooth_noise_transition = 1;
}

void			process_input(GLFWwindow *window, t_event_handler *e_handler)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		e_handler->mix_value = e_handler->mix_value >= 1.0f ? 1.0
		: e_handler->mix_value + 0.0001f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		e_handler->mix_value = e_handler->mix_value <= 0.0f ? 0.0
		: e_handler->mix_value - 0.0001f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		e_handler->noise_coef += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		e_handler->noise_coef -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		e_handler->translation_mod += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		e_handler->translation_mod -= 0.001f;
		if (e_handler->translation_mod <= 1.0f)
			e_handler->translation_mod = 1.0f;
	}
	if (e_handler->is_rot_mode)
		e_handler->rotation.y = .5f * (float)glfwGetTime();
	if (e_handler->is_smooth_transition)
		input_smooth_transition(e_handler);
	if (e_handler->is_smooth_noise_transition)
		smooth_noise_transition(e_handler);
}

/*
** ----------------------register events--------------------------
*/

void			ft_event_handler_init(t_env *env)
{
	glfwSetScrollCallback(env->window, scroll_callback);
	glfwSetCursorPosCallback(env->window, cursor_position_callback);
	glfwSetMouseButtonCallback(env->window, mouse_button_callback);
	glfwSetKeyCallback(env->window, key_callback);
	env->e_handler = &g_e;
	env->e_handler->is_left_click = 0;
	env->e_handler->is_scale_mode = 0;
	env->e_handler->is_rot_mode = 1;
	env->e_handler->is_smooth_transition = 0;
	env->e_handler->is_smooth_noise_transition = 0;
	env->e_handler->noise_coef = 0.0f;
	env->e_handler->is_shading = 0;
	env->e_handler->initial_trans_time = 0;
	env->e_handler->mix_value = .0f;
	env->e_handler->scale_factor = 1.0f;
	env->e_handler->rel_mouse_xpos = 0;
	env->e_handler->rel_mouse_ypos = 0;
	env->e_handler->mouse_xpos_old = 0;
	env->e_handler->mouse_ypos_old = 0;
	env->e_handler->translation = (t_vec3f){.0f, .0f, 10.0f};
	env->e_handler->translation_mod = 2.0f;
	env->e_handler->rot_angle = -55.0f;
	env->e_handler->rotation = (t_vec3f){1.0f, 0.0f, 0.0f};
	env->e_handler->height = WINDOW_HEIGHT;
	env->e_handler->width = WINDOW_WIDTH;
}
