#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	variantColor;

uniform sampler2D tex0Sampler;

uniform float mixValue;

float rand(vec2 co){
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main(void)
{
	// FragColor = vec4(variantColor, 1.0);
	FragColor = mix(texture(tex0Sampler, TexCoord), vec4(variantColor, 1.0), mixValue);
}
