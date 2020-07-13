/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/13 11:06:44 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h" 

void		ft_model_world_view(t_event_handler *e, t_mat4f *result)
{
	t_mat4f identity;
	t_mat4f model;
	t_mat4f view;
	t_mat4f projection;

	identity = ft_mat4f_create_init(e->scaleFactor);
	model = ft_mat4f_rotation_xyz(ft_to_radf(e->rot_angle), e->rotation);
	view = ft_mat4f_translate(identity, e->translation);
	projection = ft_perspective_matrixf(ft_to_radf(45.0f), (float)((float)e->width / (float)e->height), 0.1f, 100.0f);
	(*result) = ft_mat4f_x_mat4f(model, ft_mat4f_x_mat4f(view, projection));
}

t_texture	*load_texture(char *path, t_shader *shader)
{
	t_texture *tex;

	if(path
	&& (tex = texture_construct())
	&& tex
	->load(tex, path)
	->bind(tex, GL_TEXTURE_2D, 0)
	->set_params(tex, (t_tex_params){WRAP_R, WRAP_R, 0, FILTER_N, FILTER_N})
	->exec(tex))
	{
	//	bind textures to shader >> no need to bind inside loop
		shader->set_int(shader, "texSampler", tex->bind_id); // default is 0 // tell OpenGL that tex0Sampler belongs to texture unit 0 (previously set in bind() function)
		return (tex);
	}
	return (NULL);
}

void		cleanup(t_env *env)
{
	// -------------- cleanup --------------
	glDeleteVertexArrays(1, &env->VAO);
	glDeleteBuffers(1, &env->EBO);
	glDeleteBuffers(1, &env->VBO);
	glfwTerminate();
	if (env->obj) ft_destroy_object(&env->obj);
	if(env->tex) env->tex->destroy(&env->tex);
	if(env->shader) ft_memdel((void **)&env->shader);
}

int			main(int argc, char **argv)
{
	t_event_handler *e;
	t_env			env;

	if (!(env.obj = ft_obj_from_args(argc, argv)))
		return (0);
	if (!ft_convert_object(env.obj))
		return (0);
	if (!init_setup(&env.window, WINDOW_WIDTH, WINDOW_WIDTH, "OpenGL"))
		return (-1);
	e = ft_event_handler_init(env.window); // must be init after init_setup()
	if (!(env.shader = shader_construct("src/shaders/shaderSource/vertex.glsl", "src/shaders/shaderSource/fragment.glsl")))
	{
		glfwTerminate();
		return (-1);
	}
	env.shader->use(env.shader); // must use shader before setting uniform values

	env.tex = load_texture(argc > 2 ? argv[2] : NULL, env.shader);
//---------------------------------
	glGenBuffers(1, &env.VBO);
	glGenVertexArrays(1, &env.VAO);
	glGenBuffers(1, &env.EBO);

// -- bind buffers --
	if (env.obj->flags & F_INDEX && env.obj->flags & F_TEXTURE_INDEX)
	{
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(env.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, env.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * env.obj->vertices_len * 5, env.obj->vertices_array, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * env.obj->indices_len * 3, env.obj->vindices_array, GL_STATIC_DRAW);

	// specify how data should be interpreted
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //applies to the currently bound VBO to GL_ARRAY_BUFFER
		glEnableVertexAttribArray(0); // enable location 0

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved_textures.png
		glEnableVertexAttribArray(1); // enable location 1
	}
	else if (env.obj->flags & F_INDEX == F_INDEX)
	{
		glBindVertexArray(env.VAO);
		glBindBuffer(GL_ARRAY_BUFFER, env.VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * env.obj->vertices_len * 3, env.obj->vertices_array, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * env.obj->indices_len * 3, env.obj->vindices_array, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
}

//window loop
	while(!glfwWindowShouldClose(env.window))
	{
		ft_fps_print();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and z-buffer
		glfwPollEvents();
		processInput(env.window);
		env.shader->set_float(env.shader, "scaleFactor", e->scaleFactor);
		env.shader->set_float(env.shader, "mixValue", e->mixValue);
// -----------------Transform Matrix--------------------
		ft_model_world_view(e, &env.final_matrix);
// --------------set uniform that's in vertex shader---------
		env.shader->set_mat4f(env.shader, "final_matrix", (const t_mat4f *)&env.final_matrix);
// -----------------------------------------------------------
		glBindVertexArray(env.VAO);
		glDrawElements(GL_TRIANGLES, env.obj->indices_len * 3, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(env.window);
	}
	cleanup(&env);
	return (0);
}
