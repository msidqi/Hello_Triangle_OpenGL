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
        mixValue += 0.01f;
        if(mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mixValue -= 0.01f;
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		translation.y += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		translation.y -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		translation.x += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		translation.x -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		translation.z += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		translation.z -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		rotation.x += .1f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		rotation.x -= .1f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		rotation.y += .1f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		rotation.y -= .1f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		rotation.z += .1f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		rotation.z -= .1f;
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
	glEnable(GL_DEPTH_TEST);
	return (1);
}

t_mat4f mat4_to_mat4f(t_mat4 mat)
{
	t_mat4f ret;
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			ret.v[i][j] = (float)mat.v[i][j];
		}
	}
	return (ret);
}

int		main(int argc, char **argv)
{
	GLFWwindow	*window;
	t_shader	*shader;
	// t_obj		*obj;

	// obj = ft_obj_from_args(argc, argv);
	// ft_print_indices(obj);
	// ft_print_vertices(obj);
	// ft_destroy_object(&obj);
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
	glEnableVertexAttribArray(2);

// ------------------------------------------------
//window loop
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
		t_mat4f result;

		identity = ft_mat4f_create();
		model = ft_mat4f_rotation_xyz(ft_to_radf(rot_angle), rotation);
		view = ft_mat4f_translate(identity, translation);
		projection = ft_perspective_matrixf(ft_to_radf(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		result = ft_mat4f_x_mat4f(model, ft_mat4f_x_mat4f(view, projection));

// --------------set uniform that's in vertex shader---------
		shader->set_mat4f(shader, "model", &model);
		shader->set_mat4f(shader, "view", &view);
		shader->set_mat4f(shader, "projection", &projection);
		shader->set_mat4f(shader, "result", (const t_mat4f *)&result);
// -----------------------------------------------------------
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/*glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

		glfwSwapBuffers(window);
	}
	// cleanup ---------------------------
	glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	if(tex0) tex0->destroy(&tex0);
	if(tex1) tex1->destroy(&tex1);
	if(shader) free(shader);
	return (0);
}
