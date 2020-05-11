#version 330 core

/*
** use glVertexAttribPointer's position parameter to specify to OpenGL
** the location of the vertex-attribute(in vertex data) that you want to configure(pass data to)
**
** example of vec3 vertex-attribute:
** glVertexAttribPointer((position = 0), (size of vertex-attribute = 3), GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
*/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 transform;

void main(void)
{
	gl_Position = transform * vec4(aPos.xyz, 1.0);
	ourColor = aCol;
	TexCoord = aTexCord;
}