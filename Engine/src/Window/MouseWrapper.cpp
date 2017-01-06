#include "MouseWrapper.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace dbr
{
    namespace gl
    {
        namespace Mouse
        {
            constexpr int MOUSE_BUTTON_1()
            {
                return GLFW_MOUSE_BUTTON_1;
            }
        }
    }
}