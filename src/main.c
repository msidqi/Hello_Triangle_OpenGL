/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/07 23:26:31 by msidqi           ###   ########.fr       */
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
	projection = ft_perspective_matrixf(ft_to_radf(45.0f),
				(float)((float)e->width / (float)e->height), 0.1f, 100.0f);
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

/*
** stride == total_num_of_elements =>
** [|v0, v1, v2,| |v3, v4|]
** [|vertexdata | |colors|]
** number_of_elements equals 3 for vertexdata and 2 for colors
** 
** index_in_stride is the starting point =>
** 		0 (v0) for vertexdata and 3 (v3) for colors
*/

void	describe_buffer(GLuint location, GLint number_of_elements,
		GLenum gl_type, GLboolean normalized, GLsizei stride,
		GLuint index_in_stride, unsigned long type_size)
{
	// specify how data should be interpreted
	glVertexAttribPointer(location, number_of_elements, gl_type, normalized,
			stride * type_size, (const void *)(index_in_stride * type_size)); //applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(location); // enable location 0
}

void	generate_buffer(unsigned int *vbo)
{
	glGenBuffers(1, vbo);
}

void	bind_buffer(GLuint target_buffer, GLuint buffer,
		unsigned long buffer_size, const void *data)
{
	glBindBuffer(target_buffer, buffer);
	glBufferData(target_buffer, buffer_size, data, GL_STATIC_DRAW);
}

void	generate_vao(GLuint *vao)
{
	glGenVertexArrays(1, vao);
}

void	bind_vao(GLuint vao)
{
	glBindVertexArray(vao);
}

void	handle_buffers(t_env *env)
{
	t_obj *obj;

	obj = env->obj;
	// -- generate buffers --
	generate_buffer(&env->VBO);
	generate_vao(&env->VAO);
	generate_buffer(&env->EBO);
	// -- bind buffers --
	if (obj->flags & F_INDEX && obj->flags & F_TEXTURE_INDEX)
	{
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		bind_vao(env->VAO);
		bind_buffer(GL_ARRAY_BUFFER, env->VBO,
		sizeof(float) * obj->vertices_len * 5, obj->vertices_array);
		bind_buffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO,
		sizeof(unsigned int) * obj->indices_len * 3, obj->vindices_array);
		describe_buffer(0, 3, GL_FLOAT, GL_FALSE, 5, 0, sizeof(float));
		describe_buffer(1, 2, GL_FLOAT, GL_FALSE, 5, 3, sizeof(float));
	}
	else if ((obj->flags & F_INDEX) == F_INDEX)
	{
		bind_vao(env->VAO);
		bind_buffer(GL_ARRAY_BUFFER, env->VBO,
		sizeof(float) * obj->vertices_len * 3, obj->vertices_array);
		bind_buffer(GL_ELEMENT_ARRAY_BUFFER, env->EBO,
		sizeof(unsigned int) * obj->indices_len * 3, obj->vindices_array);
		describe_buffer(0, 3, GL_FLOAT, GL_FALSE, 3, 0, sizeof(float));
	}
}

void	handle_screen(GLFWwindow *window)
{
	glfwSwapBuffers(window);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and z-buffer
}

void	update(t_env *env)
{
	processInput(env->window);
	env->shader->set_float(env->shader, "scaleFactor", env->e_handler->scaleFactor);
	env->shader->set_float(env->shader, "mixValue", env->e_handler->mixValue);
// -----------------Transform Matrix--------------------
	ft_model_world_view(env->e_handler, &env->final_matrix);
// --------------set uniform that's in vertex shader---------
	env->shader->set_mat4f(env->shader, "final_matrix", (const t_mat4f *)&env->final_matrix);
// -----------------------------------------------------------
}

int			main(int argc, char **argv)
{
	t_env	env;
	const char *vshader_path = "src/shaders/shaderSource/vertex.glsl";
	const char *fshader_path = "src/shaders/shaderSource/fragment.glsl";

	if (!(env.obj = ft_obj_from_args(argc, argv))
	|| !ft_convert_object(env.obj)
	|| !init_opengl(&env.window, WINDOW_WIDTH, WINDOW_WIDTH, "OpenGL")
	|| !(env.shader = shader_construct(vshader_path, fshader_path)))
	{
		cleanup(&env);
		return (-1);
	}
	env.shader->use(env.shader); // must use shader before setting uniform values
	env.e_handler = ft_event_handler_init(env.window); // must be init after init_opengl()
	env.tex = load_texture(argc > 2 ? argv[2] : NULL, env.shader);
	handle_buffers(&env);
	// main loop
	while(!glfwWindowShouldClose(env.window))
	{
		ft_fps_print();
		update(&env);
		bind_vao(env.VAO);
		glDrawElements(GL_TRIANGLES, env.obj->indices_len * 3, GL_UNSIGNED_INT, 0);
		handle_screen(env.window);
		glfwPollEvents();
	}
	cleanup(&env);
	return (0);
}
