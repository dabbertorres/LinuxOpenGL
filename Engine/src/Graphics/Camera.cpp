#include "Camera.hpp"

#pragma warning(push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace dbr
{
	namespace gl
	{
		Camera::Camera(glm::vec3 pos, glm::quat rotation)
			: positionVal{pos},
			rotationVal{rotation}
		{}

		void Camera::lookAt(const glm::vec3& look)
		{
			auto cross = glm::cross(look, positionVal);
			auto dot = glm::dot(look, positionVal);

			auto lookLen = glm::length(look);
			auto posLen = glm::length(positionVal);

			lookLen *= lookLen;
			posLen *= posLen;

			glm::quat rot{glm::sqrt(lookLen * posLen) + dot, cross};

			rotationVal *= rot;
		}

		glm::vec3 Camera::face(const glm::vec3& forward) const
		{
			return rotationVal * forward;
		}

		glm::vec3 Camera::position() const
		{
			return positionVal;
		}

		void Camera::position(glm::vec3 pos)
		{
			positionVal = pos;
		}

		glm::quat Camera::rotation() const
		{
			return rotationVal;
		}

		void Camera::rotation(const glm::quat& rot)
		{
			rotationVal = glm::normalize(rot);
		}
	}
}
