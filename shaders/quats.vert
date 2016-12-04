#version 330 core

uniform mat4 projection;

uniform vec4 scale;
uniform vec4 translation;
uniform vec4 rotation;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

out vec4 vertexColor;

vec4 rotateVector(vec4 vec, vec4 quat)
{
	return vec4(vec.xyz + 2.0 * cross(cross(vec.xyz, quat.xyz) + quat.w * vec.xyz, quat.xyz), vec.w);
}

void main()
{
	gl_Position = projection * position;
	vertexColor = color;
}
