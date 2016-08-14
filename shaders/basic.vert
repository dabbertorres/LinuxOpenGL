#version 330 core

uniform mat4 transform;

layout (location = 0) in vec3 position;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
}