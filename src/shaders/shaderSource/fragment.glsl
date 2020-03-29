#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	ourColor;

uniform sampler2D outTexture1;
uniform sampler2D outTexture2;

void main(void)
{
	FragColor = mix(texture(outTexture1, TexCoord), texture(outTexture2, TexCoord), 0.5) * vec4(ourColor, 1.0);
}