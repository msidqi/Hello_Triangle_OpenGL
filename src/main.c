#include "../include/scop.h" 

#include "../include/scop.h"

t_texture	*load(t_texture *this, char *texture_path)
{
	if (!(this->data = stbi_load(texture_path, &this->w, &this->h, &this->channels, 0)))
	{
		this->error = 1;
		printf("ERROR::STBI::COULD_NOT_LOAD_IMAGE : %s\n", texture_path);
	}
	return (this);
}

/*
** texture_number starts from 0: is used to load multiple textures on GPU
*/

t_texture	*bind(t_texture *this, int gl_target, int texture_number)
{
	glGenTextures(1, &this->gl_id);
	glActiveTexture(GL_TEXTURE0 + texture_number);
	glBindTexture(gl_target, this->gl_id);
	this->gl_target = gl_target;
	return (this);
}

t_texture	*set_params(t_texture *this)
{
	if (this->gl_target == -1 || this->error == 1)
	{
		this->error = 1;
		printf("ERROR::TEXTURE::NO_BIND_TARGET\n");
	}
	else
	{
		glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set how openGL wraps textures on S axis (x)
		glTexParameteri(this->gl_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->gl_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // texture filterng option for when using small texture on bigger obj
		glTexParameteri(this->gl_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	return (this);
}

void	exec(t_texture *this)
{
	if (this->error == 1 || !this->data)
	{
		printf("ERROR::TEXTURE::EXEC\n");
	}
	else
	{
		glTexImage2D(this->gl_target, 0, GL_RGB, this->w, this->h, 0, this->channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, this->data); // generates texture on currently bound texture obj
		glGenerateMipmap(this->gl_target); // saves us form calling glTexImage2D(GL_TEXTURE_2D, 0, ...) for different levels(0)
		stbi_image_free(this->data);
		this->data = NULL;
	}
}

void		tex_destroy(t_texture *this)
{
	if (this->data)
		free(this->data);
	free(this);
}

t_texture	*texture_contruct()
{
	t_texture *this;

	if(!(this = (t_texture *)malloc(sizeof(t_texture))))
		return(NULL);
	this->error = 0;
	this->gl_target = -1;
	this->load = &load;
	this->bind = &bind;
	this->set_params = &set_params;
	this->exec = &exec;
	this->destroy = tex_destroy;
	return (this);
}

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
	if (!(shader = shader_construct("src/shaders/shaderSource/vertex.glsl", "src/shaders/shaderSource/fragment.glsl")))
	{
		printf("ERROR::SHADER::CONSTRUCTION\n");
		return (-1);
	}

	t_texture *tex;
	
	tex = texture_contruct();
	tex
	->load(tex, "texture/container.jpg")
	->bind(tex, GL_TEXTURE_2D, 0)
	->set_params(tex)->exec(tex);
//---------------------------------
	float vertices1[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	unsigned int indices[] = {  // indicies for the vetexes (used in EBO)
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// used for indexed-drawing
	unsigned int EBO;
	glGenBuffers(1, &EBO);

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
	glEnableVertexAttribArray(2);
	
//window loop
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		processInput(window);
		
		// shader->setFloat(shader, "classUniform", 0.9);
		shader->use(shader);
		glBindTexture(GL_TEXTURE_2D, tex->gl_id);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
	}
	tex->destroy(tex);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	free(shader);
	return (0);
}
