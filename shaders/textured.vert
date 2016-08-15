#version 330 core

uniform mat4 transform;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 fragColor;
out vec2 fragTexCoord;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	fragColor = color;
	fragTexCoord = texCoord;
}