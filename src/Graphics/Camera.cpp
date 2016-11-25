#include "Camera.hpp"

#pragma warning(push, 0)
#include <glm/gtc/matrix_transform.hpp>
#pragma warning(pop)

namespace dbr
{
	namespace gl
	{
		Camera::Camera(glm::vec3 position, glm::vec3 faceDir, glm::vec3 up)
			: up{up},
			position{position},
			facing{faceDir}
		{}

		void Camera::rotate(const glm::vec2& offsets)
		{
			rotate({offsets.x, offsets.y, 0});
		}

		void Camera::rotate(const glm::vec3& offsets)
		{
			glm::vec2 yaw{glm::cos(offsets.x), glm::sin(offsets.x)};
			glm::vec2 pitch{glm::cos(offsets.y), glm::sin(offsets.y)};
//			glm::vec2 roll{glm::cos(offsets.z), glm::sin(offsets.z)};

			facing.x += pitch.x * yaw.x;
			facing.y += pitch.y;
			facing.z += pitch.x * yaw.y;

			facing = glm::normalize(facing);

//			up.x += roll.x;
//			up.y += roll.y;

//			up = glm::normalize(up);
		}

		void Camera::lookAt(const glm::vec3& lookTowardsPos)
		{
			facing = glm::normalize(lookTowardsPos - position);
		}
		
		glm::mat4 Camera::view() const
		{
			return glm::lookAt(position, position + facing, up);
		}
	}
}
