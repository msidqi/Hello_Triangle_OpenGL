/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:34 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/13 01:52:26 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h" 

void	framebuffer_size_callback(GLFWwindow* window, int width, int height) // callback to resize the viewport @ window size-change
{
    glViewport(0, 0, width, height);
}

float mixValue = 0.2f;

t_vec3f translation = (t_vec3f){.0f, .0f, 3.0f};
float rot_angle = -55.0f;
t_vec3f rotation = (t_vec3f){1.0f, 0.0f, 0.0f};

void	processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mixValue += 0.0001f;
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.0001f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		translation.y += .003f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		translation.y -= .003f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		translation.x += .003f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		translation.x -= .003f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		translation.z += .003f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		translation.z -= .003f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		rotation.x += .003f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		rotation.x -= .003f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		rotation.y += .003f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		rotation.y -= .003f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		rotation.z += .003f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		rotation.z -= .003f;
}


void	ft_fps_print()
{
	static double	last_time = 0;
	static size_t	frames_count = 0;
	double			current_time;

	if (!last_time)
		last_time = glfwGetTime();
	current_time = glfwGetTime();
	frames_count++;
	if (current_time - last_time > 1.0)
	{
		printf("%f ms/frame(%zu fps)\n", 1000.0/(double)frames_count, frames_count);
		frames_count = 0;
		last_time += 1.0;
	}
}

int		init_setup(GLFWwindow **window, int width, int height, char *window_name)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // load only core OpenGL
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS to Initialize
#endif
	(*window) = glfwCreateWindow(width, height, window_name, NULL, NULL);
	if ((*window) == NULL)
	{
		printf("Failed to create GLFW window");
		return (0);
	}
	glfwMakeContextCurrent(*window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // load OpenGL functions with GLAD
	{
		printf("Failed to initialize GLAD");
		return (0);
	}
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
	return (1);
}

int		main(int argc, char **argv)
{
	GLFWwindow	*window;
	t_shader	*shader;
	t_obj		*obj = NULL;

	if (!(obj = ft_obj_from_args(argc, argv)))
	{
		printf("Object was not loaded\n");
		return (0);
	}
	ft_convert_object(obj);
	// return (0);





	window = NULL;
	if (!init_setup(&window, 800, 600, "OpenGL"))
	{
		glfwTerminate();
		return (-1);
	}
	if (!(shader = shader_construct("src/shaders/shaderSource/vertex.glsl", "src/shaders/shaderSource/fragment.glsl")))
	{
		glfwTerminate();
		printf("ERROR::SHADER::CONSTRUCTION\n");
		return (-1);
	}

	// -------Enable depth testing globally
	glEnable(GL_DEPTH_TEST);

	t_texture *tex0 = texture_construct();
	tex0
	->load(tex0, "texture/container.jpg")
	->bind(tex0, GL_TEXTURE_2D, 0)
	->set_params(tex0, (t_tex_params){WRAP_R, WRAP_R, 0, FILTER_N, FILTER_N})
	->exec(tex0);
	
	t_texture *tex1 = texture_construct();
	tex1
	->load(tex1, "texture/awesomeface.png")
	->bind(tex1, GL_TEXTURE_2D, 1)
	->set_params(tex1, (t_tex_params){WRAP_R, WRAP_R, 0, FILTER_N, FILTER_N})
	->exec(tex1);

//	bind both textures to shader >> no need to bind inside loop
	shader->use(shader); // must use shader before setting uniform values
	shader->set_int(shader, "tex0Sampler", 0); // default is 0
	shader->set_int(shader, "tex1Sampler", 1); // tell OpenGL that tex1Sampler belongs to texture unit 1 (previously set in bind() function)
//---------------------------------
	// 42.obj
	float vert[] = {
		0.232406f, -1.216630f, 1.133818f,
		0.232406f, -0.745504f, 2.843098f,
		-0.227475f, -0.745504f, 2.843098f,
		-0.227475f, -1.216630f, 1.133818f,
		0.232407f, 1.119982f, 1.133819f,
		0.232406f, 1.119982f, 1.602814f,
		-0.227475f, 1.119982f, 1.602813f,
		-0.227475f, 1.119982f, 1.133818f,
		0.232406f, -0.340316f, 2.843098f,
		-0.227475f, -0.340316f, 2.843098f,
		0.232407f, -0.305193f, 1.133819f, 
		0.232407f, -0.294496f, 2.297937f, 
		-0.227475f, -0.305193f, 1.133818f,
		-0.227475f, -0.294496f, 2.297937f,
		0.232406f, -1.222569f, 1.497195f,
		0.232406f, -0.745504f, 1.477731f,
		-0.227475f, -0.745504f, 1.477731f,
		-0.227475f, -1.222569f, 1.497194f,
		-0.227403f, -0.731178f, 0.901477f,
		-0.227403f, -0.731178f, -0.037620,
		0.223704f, -0.731178f, -0.037620f,
		0.223704f, -0.731178f, 0.901477f,
		-0.227403f, 1.119377f, 0.901477f,
		-0.227403f, 1.119377f, -0.037620f,
		0.223704f, 1.119377f, -0.037620f,
		0.223704f, 1.119377f, 0.901477f,
		-0.227403f, -0.129772f, 0.901477f,
		-0.227403f, 0.551492f, 0.384487f,
		-0.227403f, 1.104268f, 0.408501f,
		-0.227403f, 0.507336f, 0.901477f,
		0.223704f, 0.507336f, 0.901477f,
		0.223704f, 1.104269f, 0.408501f,
		0.223704f, 0.551492f, 0.384487f,
		0.223704f, -0.129772f, 0.901477f,
		-0.227403f, 0.634134f, -0.037620f,
		-0.227403f, -0.066768f, 0.398575f,
		-0.227403f, -0.684649f, 0.389681f,
		-0.227403f, -0.075523f, -0.037620f,
		0.223704f, 0.634134f, -0.037620f,
		0.223704f, -0.066768f, 0.398575f,
		0.223704f, -0.684649f, 0.389681f,
		0.223704f, -0.075523f, -0.037620f
	};
	unsigned int ind2[] = {
		15, 1, 2,
		15, 2, 16,
		4, 7, 6,
		4, 6, 5,
		28, 29, 22,
		8, 5, 6,
		8, 6, 9,
		13, 12, 16,
		10, 0, 3,
		10, 3, 12,
		1, 8, 9,
		1, 9, 2,
		4, 11, 13,
		4, 13, 7,
		11, 10, 12,
		11, 12, 13,
		0, 14, 17,
		0, 17, 3,
		14, 15, 16,
		14, 16, 17,
		37, 41, 20,
		37, 20, 19,
		32, 38, 24,
		32, 24, 31,
		33, 26, 18,
		33, 18, 21,
		18, 19, 20,
		18, 20, 21,
		25, 24, 23,
		25, 23, 22,
		25, 22, 29,
		25, 29, 30,
		30, 29, 28,
		30, 28, 31,
		31, 28, 27,
		31, 27, 32,
		32, 27, 26,
		32, 26, 33,
		23, 24, 38,
		23, 38, 34,
		34, 38, 39,
		34, 39, 35,
		35, 39, 40,
		35, 40, 36,
		36, 40, 41,
		36, 41, 37,
		25, 30, 31,
		36, 37, 19,
		20, 41, 40,
		11, 4, 5,
		24, 25, 31,
		21, 20, 40,
		7, 13, 6,
		27, 35, 26,
		9, 13, 16,
		9, 16, 2,
		32, 39, 38,
		39, 32, 33,
		10, 15, 14,
		10, 14, 0,
		13, 9, 6,
		1, 15, 11,
		1, 11, 8,
		10, 11, 15,
		39, 33, 21,
		39, 21, 40,
		11, 5, 8,
		17, 16, 12,
		17, 12, 3,
		35, 27, 34,
		36, 19, 18,
		28, 22, 23,
		18, 26, 35,
		18, 35, 36,
		23, 34, 27,
		23, 27, 28,
	};
	unsigned int ind[] = {
16,	2,	3,
16,	3,	17,
5,	8,	7,
5,	7,	6,
29,	30,	23,	
9,	6,	7,
9,	7,	10,
14,	13,	17,	
11,	1,	4,
11,	4,	13,
2,	9,	10,
2,	10,	3,
5,	12,	14,
5,	14,	8,
12,	11,	13,
12,	13,	14,
1,	15,	18,
1,	18,	4,
15,	16,	17,
15,	17,	18,
38,	42,	21,
38,	21,	20,
33,	39,	25,
33,	25,	32,
34,	27,	19,
34,	19,	22,
19,	20,	21,
19,	21,	22,
26,	25,	24,
26,	24,	23,
26,	23,	30,
26,	30,	31,
31,	30,	29,
31,	29,	32,
32,	29,	28,
32,	28,	33,
33,	28,	27,
33,	27,	34,
24,	25,	39,
24,	39,	35,
35,	39,	40,
35,	40,	36,
36,	40,	41,
36,	41,	37,
37,	41,	42,
37,	42,	38,
26,	31,	32,	
37,	38,	20,	
21,	42,	41,	
12,	5,	6,	
25,	26,	32,	
22,	21,	41,	
8,	14,	7,	
28,	36,	27,	
10,	14,	17,
10,	17,	3,
33,	40,	39,	
40,	33,	34,	
11,	16,	15,
11,	15,	1,
14,	10,	7,	
2,	16,	12,
2,	12,	9,
11,	12,	16,	
40,	34,	22,
40,	22,	41,
12,	6,	9,	
18,	17,	13,
18,	13,	4,
36,	28,	35,	
37,	20,	19,	
29,	23,	24,	
19,	27,	36,
19,	36,	37,
24,	35,	28,
24,	28,	29,
	};
	for(int i = 0; i < sizeof(ind)/sizeof(ind[0]); i++)
	{
		printf("%u \n", ind[i] - 1);
	}
	printf("max i : %zu\n", sizeof(ind2)/sizeof(ind2[0]));
	ft_print_vertices_array(obj, obj->vertices_array);
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// used for indexed-drawing
	unsigned int EBO;
	glGenBuffers(1, &EBO);

// -- bind buffers --
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);
printf("sizeof(float) * obj->vertices_len %zu == %zu sizeof (vert) ||| sizeof(unsigned int) * obj->indices_len %zu == %zu sizeof (ind)\n"
, sizeof(float) * obj->vertices_len * 3, sizeof(vert), sizeof(unsigned int) * obj->indices_len * 3, sizeof(ind));
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->vertices_len * 3, obj->vertices_array, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * obj->indices_len * 3, obj->vindices_array, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind2), ind2, GL_STATIC_DRAW);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

// specify how data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//applies to the currently bound VBO to GL_ARRAY_BUFFER
	// glEnableVertexAttribArray(1); // enable location 0

	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved_textures.png
	// glEnableVertexAttribArray(2);

	 // square
	/*float vertices1[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, .0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
     0.5f, -0.5f, .0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, .0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, .0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // top left
	};
	unsigned int indices[] = {  // indicies for the vetexes (used in EBO)
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

// -- generate buffers --
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// used for indexed-drawing
	unsigned int EBO;
	glGenBuffers(1, &EBO);

// -- bind buffers --
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

// specify how data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(1); // enable location 0

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved_textures.png
	glEnableVertexAttribArray(2);*/

	/* // cube
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

// ------------------------------------------------
//window loop
	while(!glfwWindowShouldClose(window))
	{
		ft_fps_print();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color and z-buffer


		glfwPollEvents();
		processInput(window);
		shader->set_float(shader, "mixValue", mixValue);
		shader->use(shader);
		// glBindTexture(GL_TEXTURE_2D, tex0->gl_id); // no need to bind inside loop
// -----------------Transform Matrix--------------------
		t_mat4f identity;
		t_mat4f model;
		t_mat4f view;
		t_mat4f projection;
		// t_mat4f result;

		identity = ft_mat4f_create();
		model = ft_mat4f_rotation_xyz(ft_to_radf(rot_angle), rotation);
		view = ft_mat4f_translate(identity, translation);
		projection = ft_perspective_matrixf(ft_to_radf(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		// result = ft_mat4f_x_mat4f(model, ft_mat4f_x_mat4f(view, projection));

// --------------set uniform that's in vertex shader---------
		shader->set_mat4f(shader, "model", &model);
		shader->set_mat4f(shader, "view", &view);
		shader->set_mat4f(shader, "projection", &projection);
		// shader->set_mat4f(shader, "result", (const t_mat4f *)&result);
// -----------------------------------------------------------
		/*// cube
		glDrawArrays(GL_TRIANGLES, 0, 36);*/

		// square
		// glBindVertexArray(VAO);
		// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		 // 42
		glBindVertexArray(VAO);
		// glDrawElements(GL_TRIANGLES, 47, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 76 * 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}
	// -------------- cleanup --------------
	if (obj) ft_destroy_object(&obj);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	if(tex0) tex0->destroy(&tex0);
	if(tex1) tex1->destroy(&tex1);
	if(shader) free(shader);
	return (0);
}
