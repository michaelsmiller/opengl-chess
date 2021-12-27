#version 440 core

layout (location = 0) in vec4 vertexColor;

layout (location = 0) out vec4 fragColor;

// uniform vec4 defaultColor;
uniform float time_val;

void main()
{
	// fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	fragColor = vertexColor;
	// fragColor = vec4(0., time_val, 0., 1.);
} 
