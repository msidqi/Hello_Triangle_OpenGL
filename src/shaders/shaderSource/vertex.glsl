#version 400 core

/*
** use glVertexAttribPointer's position parameter to specify to OpenGL
** the location of the vertex-attribute(in vertex data) that you want to configure(pass data to)
**
** example of vec3 vertex-attribute:
** glVertexAttribPointer((position = 0), (size of vertex-attribute = 3), GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
*/
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;

out vec3 variantColor;
out vec2 TexCoord;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;


uniform mat4 final_matrix;

void main(void)
{
	float sinPosx = sin(aPos.x);
	float sinPosy = sin(aPos.y);
	// gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
	gl_Position = final_matrix * vec4(aPos.xyz, 1.0);
	variantColor.x =  0.5 * float(sinPosx > 0) + 0.7 * float(sinPosx < 0);
	variantColor.y = 0.1 * float(sinPosy > 0) + 0.5 * float(sinPosy < 0);
	variantColor.z = 0.2;
	TexCoord = aTexCord;
}