/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/13 01:13:29 by msidqi           ###   ########.fr       */
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
	projection = ft_perspective_matrixf(ft_to_radf(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	(*result) = ft_mat4f_x_mat4f(model, ft_mat4f_x_mat4f(view, projection));
}

t_texture	*load_texture(char *path, t_shader *shader)
{
	t_texture *tex0;
	
	tex0 = texture_construct();
	tex0->load(tex0, path)->bind(tex0, GL_TEXTURE_2D, 0)
	->set_params(tex0, (t_tex_params){WRAP_R, WRAP_R, 0, FILTER_N, FILTER_N})
	->exec(tex0);
//	bind textures to shader >> no need to bind inside loop
	shader->set_int(shader, "tex0Sampler", tex0->bind_id); // default is 0 // tell OpenGL that tex0Sampler belongs to texture unit 0 (previously set in bind() function)
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
	{
		ft_putendl_fd("Object was not loaded", 2);
		return (0);
	}
	if (!ft_convert_object(env.obj))
	{
		ft_putendl_fd("could not convert object", 2);
		return (0);
	}
	if (!init_setup(&env.window, 800, 600, "OpenGL"))
	{
		ft_putendl_fd("OpenGL setup failed", 2);
		glfwTerminate();
		return (-1);
	}
	e = ft_event_handler_init(env.window); // must be init after init_setup()
	if (!(env.shader = shader_construct("src/shaders/shaderSource/vertex.glsl", "src/shaders/shaderSource/fragment.glsl")))
	{
		glfwTerminate();
		ft_putendl_fd("ERROR::SHADER::CONSTRUCTION", 2);
		return (-1);
	}
	env.shader->use(env.shader); // must use shader before setting uniform values

	env.tex = load_texture("texture/space.png", env.shader);
//---------------------------------
	// unsigned int VBO;
	glGenBuffers(1, &env.VBO);

	// unsigned int VAO;
	glGenVertexArrays(1, &env.VAO);

	// used for indexed-drawing
	// unsigned int EBO;
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
		env.shader->use(env.shader);
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
