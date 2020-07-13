/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 21:37:17 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/13 15:20:08 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h" 

t_event_handler e;

void	processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        e.mixValue += 0.0001f;
        if(e.mixValue >= 1.0f)
            e.mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        e.mixValue -= 0.0001f;
        if (e.mixValue <= 0.0f)
            e.mixValue = 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        e.translation_mod += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    {
        e.translation_mod -= 0.001f;
        if (e.translation_mod <= 1.0f)
            e.translation_mod = 1.0f;
	}
	if (e.isRotMode)
		e.rot_angle = (float)glfwGetTime() * 20.0f;
	if (e.isSmoothTransition)
	{
		if (e.initialTransTime == .0f)
			e.initialTransTime = (float)glfwGetTime();
		if (e.isSmoothTransition == 1)
			e.mixValue -= ((float)glfwGetTime() - e.initialTransTime) / 10000.0f;
		if (e.mixValue <= 0.0f)
		{
            e.mixValue = .0f;
			e.isSmoothTransition = 0;
			e.initialTransTime = .0f;
		}
	}
}

void	scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (e.isRightClick)
	{
		if (yoffset > 0)
			e.rotation.z += .05f;
		if (yoffset < 0)
			e.rotation.z -= .05f;
		e.isScaleMode = 0;
	}
	else if (e.isScaleMode)
	{
		if (yoffset > 0)
			e.scaleFactor += 0.1f;
		if (yoffset < 0)
			e.scaleFactor -= 0.1f;
	}
	else
	{
		if (yoffset > 0)
			e.translation.z += .3f * e.translation_mod;
		if (yoffset < 0)
			e.translation.z -= .3f * e.translation_mod;
	}
}

void	cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	e.rel_mouse_xpos = xpos - e.mouse_xpos_old;
	e.rel_mouse_ypos = ypos - e.mouse_ypos_old;
	if (e.isLeftClick)
	{
		e.translation.y += e.translation_mod * .003f * -e.rel_mouse_ypos;
		e.translation.x += e.translation_mod * .003f * e.rel_mouse_xpos;
	}
	if (e.isRightClick)
	{
		e.rotation.y += .005f * e.rel_mouse_xpos;
		e.rotation.x += .005f * e.rel_mouse_ypos;
	}
	e.mouse_xpos_old = xpos;
	e.mouse_ypos_old = ypos;
}

void	mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		e.isLeftClick = 1;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		e.isLeftClick = 0;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		e.isRightClick = 1;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		e.isRightClick = 0;
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_S)
			e.isScaleMode = !e.isScaleMode;
		if (key == GLFW_KEY_R)
			e.isRotMode = !e.isRotMode;
		if (key == GLFW_KEY_T)
			e.isSmoothTransition = !e.isSmoothTransition;
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		if (key == GLFW_KEY_1)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (key == GLFW_KEY_2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if (key == GLFW_KEY_3)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
}

t_event_handler	*ft_event_handler_init(GLFWwindow *window)
{
	// ----------------------register events--------------------------
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	e.isLeftClick = 0;
	e.isScaleMode = 0;
	e.isRotMode = 1;
	e.isSmoothTransition = 0;
	e.initialTransTime = 0;
	e.mixValue = 1.0f;
	e.scaleFactor = 1.0f;
	e.rel_mouse_xpos = 0;
	e.rel_mouse_ypos = 0;
	e.mouse_xpos_old = 0;
	e.mouse_ypos_old = 0;
	e.translation = (t_vec3f){.0f, .0f, 3.0f};
	e.translation_mod = 1.0f;
	e.rot_angle = -55.0f;
	e.rotation = (t_vec3f){1.0f, 0.0f, 0.0f};
	e.height = WINDOW_HEIGHT;
	e.width = WINDOW_WIDTH;
	return (&e);
}

/*
* callback to resize the viewport @ window size-change
*/

void			framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	e.height = height;
	e.width = width;
    glViewport(0, 0, width, height);
}
