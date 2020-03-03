#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

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

char	*read_shader_file(const char *file_name)
{
	FILE		*fd;
	char		*shader_buffer;
	size_t		shader_size;//, log_size;

	if ((fd = fopen(file_name, "r")) == NULL)
	{
		printf("ERROR::OPEN::COULD_NOT_OPEN_FILE : %s\n", file_name);
		return(NULL);
	}
	fseek(fd, 0, SEEK_END);
	shader_size = ftell(fd);
	rewind(fd);
	if (!(shader_buffer = (char *)malloc(shader_size + 1)))
	{
		printf("ERROR::MALLOC::OUT_OF_MEMORY\n");
		return (NULL);
	}
	shader_buffer[shader_size] = '\0';
	fread(shader_buffer, sizeof(char), shader_size, fd);
	fclose(fd);
	return (shader_buffer);
}

void	create_compile_shader(const char *shader_source, unsigned int *shader, int shader_type)
{
	int  success;
	char info_log[512];
	const char *type = (shader_type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";

	*shader = glCreateShader(shader_type);
	glShaderSource(*shader, 1, &shader_source, NULL); // 1: how many strings are passed as src code
	glCompileShader(*shader);
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, info_log);
		printf("ERROR::SHADER::%s::COMPILATION_FAILED\n%s\n", type, info_log);
	}
}

void	create_link_program(unsigned int *shader_program, unsigned int vertex_shader, unsigned int fragment_shader)
{
	int  success;
	char info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vertex_shader);
	glAttachShader(*shader_program, fragment_shader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		printf("ERROR::PROGRAM::LINKING_FAILED\n%s\n", info_log);
	}
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
//reading/creating/compiling vertex shader
	char *vertexShaderSource;
	if (!(vertexShaderSource = read_shader_file("src/vertex_shader.glsl")))
		return (-1);
	unsigned int vertexShader;
	create_compile_shader((const char *)vertexShaderSource, &vertexShader, GL_VERTEX_SHADER);
	
//reading/creating/compiling fragment shader
	char *fragmentShaderSource[2];
	if (!(fragmentShaderSource[0] = read_shader_file("src/fragment_shader0.glsl")))
		return (-1);
	if (!(fragmentShaderSource[1] = read_shader_file("src/fragment_shader1.glsl")))
		return (-1);
	unsigned int fragmentShader[2];
	create_compile_shader(fragmentShaderSource[0], &fragmentShader[0], GL_FRAGMENT_SHADER);
	create_compile_shader(fragmentShaderSource[1], &fragmentShader[1], GL_FRAGMENT_SHADER);

// creating program/linking shaders to program
	unsigned int shaderProgram[2];
	create_link_program(&shaderProgram[0], vertexShader, fragmentShader[0]);
	create_link_program(&shaderProgram[1], vertexShader, fragmentShader[1]);

//	free shaders / shaders source code
	glDeleteShader(vertexShader);
	free(vertexShaderSource);
	glDeleteShader(fragmentShader[0]);
	glDeleteShader(fragmentShader[1]);
	free(fragmentShaderSource[0]);
	free(fragmentShaderSource[1]);

	
//--------------------------------------------------------------------------------------
/*
** all next VBO, EBO i.e glVertexAttribPointer glEnableVertexAttribArray calls will be stored inside this VAO
** now you can bind this VAO in render loop without the need to configure each VBO,EBO (with glBindVertexArray(VAO); again)
*/

//vertex input-------------------
	float vertices0[] = {
    -0.5f, 0.5f, 0.0f,	// top
    -0.9f, -0.5f, 0.0f,	// bottom left
	-0.1f, -0.5f, 0.0f,	// bottom right
	};
	float vertices1[] = {
	0.5f, 0.5f, 0.0f,	// top
    0.1f, -0.5f, 0.0f,	// bottom left
	0.9f, -0.5f, 0.0f,	// bottom right
	};

	unsigned int VBO[2];
	glGenBuffers(2, VBO);

	unsigned int VAO[2];
	glGenVertexArrays(2, VAO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0
	// glBindVertexArray(0); // unbind VAO_0

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
// specify how data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0

//window loop
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		processInput(window);

		glUseProgram(shaderProgram[0]);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram[1]);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(2, &VAO[0]);
	// glDeleteBuffers(1, &EBO);
	glDeleteBuffers(2, &VBO[0]);
	glfwTerminate();
	return (0);
}
