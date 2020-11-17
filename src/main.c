/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/17 20:42:01 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void		cleanup(t_env *env)
{
	if (env->vao)
		glDeleteVertexArrays(1, &env->vao);
	if (env->ebo)
		glDeleteBuffers(1, &env->ebo);
	if (env->vbo)
		glDeleteBuffers(1, &env->vbo);
	if (env->window)
		glfwDestroyWindow(env->window);
	glfwTerminate();
	if (env->obj)
		ft_destroy_object(&env->obj);
	if (env->tex)
		env->tex->destroy(&env->tex);
	if (env->shader)
		ft_memdel((void **)&env->shader);
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
	e->window = NULL;
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
	if (((e.obj->flags & F_TEXTURE_INDEX) && e.tex))
		e.shader->set_float(e.shader, "hasTexture", 2);
	else
		e.shader->set_float(e.shader, "hasTexture", e.tex ? 1 : 0);
	handle_buffers(&e);
	while (!glfwWindowShouldClose(e.window))
	{
		main_loop(&e);
	}
	cleanup(&e);
	return (0);
}
