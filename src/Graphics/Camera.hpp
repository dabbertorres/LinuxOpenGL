#ifndef DBR_GL_CAMERA_HPP
#define DBR_GL_CAMERA_HPP

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning(pop)

namespace dbr
{
	namespace gl
	{
		class Camera
		{
		public:
			Camera(glm::vec3 pos = {0, 0, 0}, glm::vec3 face = {0, 0, 1}, glm::vec3 up = {0, 1, 0});

			// assumes radians
			void rotate(const glm::vec2& offsets);
			void rotate(const glm::vec3& offsets);

			void lookAt(const glm::vec3& lookTowardsPos);

			glm::mat4 view() const;

			glm::vec3 position;
			glm::vec3 facing;	// normalized
			glm::vec3 up;		// normalized
		};
	}
}

#endif
