#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	ourColor;

uniform sampler2D tex0Sampler;
uniform sampler2D tex1Sampler;

uniform float mixValue;

void main(void)
{
	FragColor = vec4(1.0, 0.2, 0.0, 1.0);
	// FragColor = mix(texture(tex0Sampler, TexCoord), texture(tex1Sampler, -TexCoord), mixValue);
	// FragColor = mix(texture(tex0Sampler, TexCoord), texture(tex1Sampler, -TexCoord), mixValue) * vec4(ourColor, 1.0);
}
