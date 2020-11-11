#version 400 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3	variantColor;

uniform sampler2D texSampler;

uniform float mix_value;
uniform float noise_coef;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}
void main(void)
{
	vec2 i = floor(TexCoord * noise_coef * 10);
	vec2 f = fract(TexCoord * noise_coef * 10);
	vec4 color = vec4(vec3(random(i)),1.0);
	// FragColor = vec4(variantColor, 1.0);
	// FragColor = mix(vec4(variantColor, 1.0), color, .5);
	// FragColor = mix(texture(texSampler, TexCoord), vec4(variantColor, 1.0), mix_value);
	FragColor = texture(texSampler, TexCoord);
}
