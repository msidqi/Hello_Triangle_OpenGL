/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/14 11:10:11 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		cleanup(t_env *env)
{
	glDeleteVertexArrays(1, &env->vao);
	glDeleteBuffers(1, &env->ebo);
	glDeleteBuffers(1, &env->vbo);
	glfwTerminate();
	if (env->obj)
		ft_destroy_object(&env->obj);
	if (env->tex)
		env->tex->destroy(&env->tex);
	if (env->shader)
		ft_memdel((void **)&env->shader);
}

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
	env->shader->set_float(env->shader, "noise_coef",
									env->e_handler->noise_coef);
	ft_model_world_view(env->e_handler, &env->final_matrix);
	env->shader->set_mat4f(env->shader, "final_matrix",
									(const t_mat4f *)&env->final_matrix);
}

static void		init_env(t_env *e)
{
	e->e_handler = NULL;
	e->tex = NULL;
	e->obj = NULL;
	e->shader = NULL;
	e->window = NULL;
	e->vs_path = VERTEX_SHADER_PATH;
	e->fs_path = FRAGEMENT_SHADER_PATH;
}

int				main(int argc, char **argv)
{
	t_env		e;

	init_env(&e);
	if (!(e.obj = ft_obj_from_args(argc, argv)) || !ft_convert_object(e.obj)
	|| !init_opengl(&e.window, WINDOW_WIDTH, WINDOW_WIDTH, WINDOW_NAME)
	|| !(e.shader = shader_construct(e.vs_path, e.fs_path)))
	{
		cleanup(&e);
		return (0);
	}
	e.shader->use(e.shader);
	ft_event_handler_init(&e);
	e.tex = load_texture(argc > 2 ? argv[2] : NULL, e.shader);
	handle_buffers(&e);
	while (!glfwWindowShouldClose(e.window))
	{
		update(&e);
		bind_vao(e.vao);
		glDrawElements(GL_TRIANGLES, e.obj->indices_len * 3,
												GL_UNSIGNED_INT, 0);
		handle_screen(e.window);
		glfwPollEvents();
	}
	cleanup(&e);
	return (0);
}
