#version 330 core

/*
** use glVertexAttribPointer's position parameter to specify to OpenGL
** the location of the vertex-attribute(in vertex data) that you want to configure(pass data to)
**
** example of vec3 vertex-attribute:
** glVertexAttribPointer((position = 0), (size of vertex-attribute = 3), GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
*/
layout (location = 0) in vec3 aPos;

void main(void)
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}