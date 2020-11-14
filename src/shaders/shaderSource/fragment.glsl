#version 400 core
out vec4 FragColor;

in vec2 TexCoord;
in vec2 TexCoordDefault;
in vec3	shadingColor;
flat in vec3 polyColor;

uniform sampler2D texSampler;

uniform float isShading;
uniform float hasTexture;
uniform float mix_value;
uniform float noise_coef;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}
void main(void)
{
	if (noise_coef > .0f)
	{
		vec2 i = floor(TexCoord * noise_coef * 10);
		vec2 f = fract(TexCoord * noise_coef * 10);
		vec4 noiseColor = vec4(vec3(random(i)),1.0);
		FragColor = noiseColor;
	}
	else if (bool(isShading))
		FragColor = vec4(shadingColor, 1.0);
	else if (bool(hasTexture))
		FragColor = mix(vec4(polyColor, 1.0), texture(texSampler, hasTexture == 1 ? TexCoordDefault : TexCoord), mix_value);
	else
		FragColor = vec4(polyColor, 1.0);
}
