#ifndef DBR_ENG_GFX_CAMERA_HPP
#define DBR_ENG_GFX_CAMERA_HPP

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#pragma warning(pop)

namespace dbr
{
    namespace eng
    {
        namespace gfx
        {
            class Camera
            {
            public:
                Camera(glm::vec3 pos = {0, 0, 0}, glm::quat rotation = glm::quat{});

                void lookAt(const glm::vec3& lookTowardsPos);

                glm::vec3 face(const glm::vec3& forward = {0.f, 0.f, 1.f}) const;

                glm::vec3 position() const;
                void position(glm::vec3 pos);

                glm::quat rotation() const;
                void rotation(const glm::quat& rot);

            private:
                glm::vec3 positionVal;
                glm::quat rotationVal;
            };
        }
    }
}

#endif
