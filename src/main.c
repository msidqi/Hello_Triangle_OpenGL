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

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
/*
** next VBO, EBO i.e glVertexAttribPointer glEnableVertexAttribArray calls will be stored inside this VAO
** now you can bind this VAO in render loop without the need to configure each VBO (with glBindVertexArray(VAO); again)
*/

//vertex input-------------------
	float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
	};
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// specify how data should be interpreted
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//applies to the currently bound VBO to GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0); // enable location 0
//reading/creating/compiling vertex shader
	char *vertexShaderSource;
	if (!(vertexShaderSource = read_shader_file("src/vertex_shader.glsl")))
		return (-1);
	unsigned int vertexShader;
	create_compile_shader((const char *)vertexShaderSource, &vertexShader, GL_VERTEX_SHADER);
	
//reading/creating/compiling fragment shader
	char *fragmentShaderSource;
	if (!(fragmentShaderSource = read_shader_file("src/fragment_shader.glsl")))
		return (-1);
	unsigned int fragmentShader;
	create_compile_shader(fragmentShaderSource, &fragmentShader, GL_FRAGMENT_SHADER);

// creating program/linking shaders to program
	unsigned int shaderProgram;
	create_link_program(&shaderProgram, vertexShader, fragmentShader);

	glDeleteShader(vertexShader);
	free(vertexShaderSource);
	glDeleteShader(fragmentShader);
	free(fragmentShaderSource);

//window loop
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		processInput(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return (0);
}
