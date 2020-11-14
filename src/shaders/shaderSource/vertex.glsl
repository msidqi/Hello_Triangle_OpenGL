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
layout (location = 2) in vec3 objectColor;

out vec3 shadingColor;
flat out vec3 polyColor;
out vec2 TexCoordDefault;
out vec2 TexCoord;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;
// gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);

uniform mat4 final_matrix;

void main(void)
{
	float sinPosx = sin(aPos.x * 100);
	float sinPosy = sin(aPos.y * 100);
	float sinPosz = sin(aPos.z * 100);
	gl_Position = final_matrix * vec4(aPos, 1.0);
	shadingColor = sinPosx * sinPosy * sinPosy * vec3(.46f, .2f, .0f);
	TexCoord = aTexCord;
	TexCoordDefault = aPos.yz;
	polyColor = objectColor;
}