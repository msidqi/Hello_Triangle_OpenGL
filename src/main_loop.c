/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/17 20:39:39 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		handle_screen(GLFWwindow *window)
{
	glfwSwapBuffers(window);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static void		update(t_env *env)
{
	ft_fps_print();
	process_input(env->window, env->e_handler);
	env->shader->set_float(env->shader, "scale_factor",
									env->e_handler->scale_factor);
	env->shader->set_float(env->shader, "mix_value",
									env->e_handler->mix_value);
	env->shader->set_float(env->shader, "isShading",
									env->e_handler->is_shading);
	env->shader->set_float(env->shader, "noise_coef",
									env->e_handler->noise_coef);
	ft_model_world_view(env->e_handler, &env->final_matrix);
	env->shader->set_mat4f(env->shader, "final_matrix",
									(const t_mat4f *)&env->final_matrix);
}

void			main_loop(t_env *e)
{
	update(e);
	bind_vao(e->vao);
	glDrawElements(GL_TRIANGLES, e->obj->indices_len * 3,
											GL_UNSIGNED_INT, 0);
	handle_screen(e->window);
	glfwPollEvents();
}
