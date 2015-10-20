#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <map>

using Vector3f = std::array<float, 3>;
using Color4f = std::array<float, 4>;

class Cube
{
	public:
	Cube();
	Cube(float size);

	void setPosition(float x, float y, float z);
	void setPosition(const Vector3f& vertex);
	Vector3f getPosition() const;

	void setRotation(float rot, const Vector3f& axis);
	void removeRotation(const Vector3f& axis);
	float getRotation(const Vector3f& axis) const;

	void setColor(unsigned int idx, const Color4f& color);
	Color4f getColor(unsigned idx) const;

	void setSize(float size);
	float getSize() const;

	void draw(const Vector3f& origin);

	private:
	// left top front
	// left bot front
	// right bot front
	// right top front

	// left top back
	// left bot back
	// right bot back
	// right top back
	std::array<float, 8 * 3> vertices;	// 8 vertices * 3 dimensions per vertex
	std::array<float, 8 * 4> colors;	// 8 colors * 4 channels per color

	Vector3f position;

	std::array<unsigned int, 36> indices;

	std::map<Vector3f, float> rotations;
};

#endif CUBE_HPP
