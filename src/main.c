#include "../include/scop.h" 

void	framebuffer_size_callback(GLFWwindow* window, int width, int height) // callback to resize the viewport @ window size-change
{
    glViewport(0, 0, width, height);
}

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
}

int		init_setup(GLFWwindow **window, int width, int height, char *window_name)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

int		main(void)
{
	GLFWwindow* window;
	t_shader *shader;

	window = NULL;
	if (!init_setup(&window, 800, 600, "OpenGL"))
	{
		glfwTerminate();
		return (-1);
	}
	if (!(shader = shader_contruct("src/shaderSource/vertex.glsl", "src/shaderSource/fragment.glsl")))
	{
		printf("ERROR::SHADER::CONSTRUCTION\n");
		return (-1);
	}
	float vertices1[] = {
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,	// top
    0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,	// bottom left
	0.9f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,	// bottom right
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
// specify how data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (float), (void*)(3 * sizeof(float))/* pointer to the first color element in vertex data*/);
	glEnableVertexAttribArray(1); // enable location 1

//window loop
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		processInput(window);
		
		// shader->setFloat(shader, "classUniform", 0.9);
		shader->use(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(2, &VAO);
	// glDeleteBuffers(1, &EBO);
	glDeleteBuffers(2, &VBO);
	glfwTerminate();
	free(shader);
	return (0);
}
