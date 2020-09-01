#version 330 core

out vec4 fragColor;
in vec2 fragPos;

uniform float time = 0.0;

void main()
{
	fragColor = vec4(1.0, 1.0, 0.5, 1.0);
	fragColor = vec4(fragPos.x, fragPos.y, 0.0, 1.0);
	fragColor.b += cos(time * 0.005);
	//fragColor.r = fragPos.x;
}