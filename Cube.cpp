#include "Cube.hpp"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <GL/gl.h>

Cube::Cube()
:	vertices(),
	colors(),
	position(),
	indices
{
	// front face
	0, 1, 2,
	0, 2, 3,

	// right face
	3, 2, 6,
	3, 6, 7,

	// top face
	0, 3, 7,
	0, 7, 4,

	// bot face
	1, 2, 6,
	1, 6, 5,

	// left face
	1, 0, 4,
	4, 5, 1,

	// back face
	5, 4, 6,
	7, 6, 4,
}
{}

Cube::Cube(float size)
:	Cube()
{
	setSize(size);
}

void Cube::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Cube::setPosition(const Vector3f& vertex)
{
	position = vertex;
}

Vector3f Cube::getPosition() const
{
	return position;
}

void Cube::setRotation(float rot, const Vector3f& axis)
{
	rotations[axis] = rot;
}

void Cube::removeRotation(const Vector3f& axis)
{
	rotations.erase(axis);
}

float Cube::getRotation(const Vector3f& axis) const
{
	return rotations.at(axis);
}

void Cube::setColor(unsigned int idx, const Color4f& color)
{
	colors[idx * 4 + 0] = color[0];
	colors[idx * 4 + 1] = color[1];
	colors[idx * 4 + 2] = color[2];
	colors[idx * 4 + 3] = color[3];
}

Color4f Cube::getColor(unsigned idx) const
{
	return{
		colors[idx * 4 + 0],
		colors[idx * 4 + 1],
		colors[idx * 4 + 2],
		colors[idx * 4 + 3],
	};
}

void Cube::setSize(float size)
{
	// use half size for dimensions from center
	size /= 2.f;

	vertices[0] = -size; vertices[1] = size; vertices[2] = size;
	vertices[3] = -size; vertices[4] = -size; vertices[5] = size;
	vertices[6] = size; vertices[7] = -size; vertices[8] = size;
	vertices[9] = size; vertices[10] = size; vertices[11] = size;

	vertices[12] = -size; vertices[13] = size; vertices[14] = -size;
	vertices[15] = -size; vertices[16] = -size; vertices[17] = -size;
	vertices[18] = size; vertices[19] = -size; vertices[20] = -size;
	vertices[21] = size; vertices[22] = size; vertices[23] = -size;
}

float Cube::getSize() const
{
	// first positive value in vertex array
	return vertices[1] * 2;
}

void Cube::draw(const Vector3f& origin)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices.data());
	glColorPointer(4, GL_FLOAT, 0, colors.data());

	glLoadIdentity();

	glTranslatef(origin[0], origin[1], origin[2]);

	// move to cube's center
	glTranslatef(position[0], position[1], position[2]);

	// rotate around center of the cube
	for(auto& rot : rotations)
		glRotatef(rot.second, rot.first[0], rot.first[1], rot.first[2]);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}
