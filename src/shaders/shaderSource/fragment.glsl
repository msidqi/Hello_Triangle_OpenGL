#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	ourColor;

uniform sampler2D tex0Sampler;
uniform sampler2D tex1Sampler;

void main(void)
{
	FragColor = mix(texture(tex0Sampler, TexCoord), texture(tex1Sampler, -TexCoord), 0.5);// * vec4(ourColor, 1.0);
}
