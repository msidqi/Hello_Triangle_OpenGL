#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct	s_wind
{
	GLFWwindow* window;
}				t_wind;

void	framebuffer_size_callback(GLFWwindow* window, int width, int height) // callback to resize the viewport @ window size-change
{
    glViewport(0, 0, width, height);
}

void	processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int		init_setup(GLFWwindow **window, int width, int height, char *window_name)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // load only core OpenGL
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS to Initialize
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

	window = NULL;
	if (!init_setup(&window, 800, 600, "OpenGL"))
	{
		glfwTerminate();
		return (-1);
	}
	float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	while(!glfwWindowShouldClose(window))
	{
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
