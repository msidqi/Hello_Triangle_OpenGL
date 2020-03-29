#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	ourColor;

uniform sampler2D outTexture;

void main(void)
{
	FragColor = texture(outTexture, TexCoord) * vec4(ourColor, 1.0);
}