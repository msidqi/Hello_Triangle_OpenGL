#version 330 core

out vec4 FragColor;

uniform vec4 changingColor;

void main(void)
{
	FragColor = changingColor;
}