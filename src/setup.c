/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:38:17 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/07 23:00:43 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h" 

int		init_opengl(GLFWwindow **window, int width, int height, char *window_name)
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
		printf("Error: Failed to create GLFW window");
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(*window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // load OpenGL functions with GLAD
	{
		printf("Error: Failed to initialize GLAD");
		glfwTerminate();
		return (0);
	}
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
	// -------Enable depth testing globally
	glEnable(GL_DEPTH_TEST);
	return (1);
}
