#version 330 core

uniform sampler2D theTexture;

in vec4 fragColor;
in vec2 fragTexCoord;

out vec4 color;

void main()
{
	color = texture(theTexture, fragTexCoord) * fragColor;
}
