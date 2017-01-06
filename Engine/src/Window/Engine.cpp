#include "Engine.hpp"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "opengl/gl_glCore33.hpp"

namespace dbr
{
	namespace eng
	{
        namespace win
        {
            VideoMode::VideoMode(const GLFWvidmode* mode)
                : width{static_cast<uint32_t>(mode->width)},
                height{static_cast<uint32_t>(mode->height)},
                redBits{static_cast<uint32_t>(mode->redBits)},
                greenBits{static_cast<uint32_t>(mode->greenBits)},
                blueBits{static_cast<uint32_t>(mode->blueBits)},
                refreshRate{static_cast<uint32_t>(mode->refreshRate)}
            {}

            VideoMode::VideoMode(uint32_t width, uint32_t height, uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t refreshRate)
                : width{width},
                height{height},
                redBits{redBits},
                greenBits{greenBits},
                blueBits{blueBits},
                refreshRate{refreshRate}
            {}

            Engine Engine::instance;

            Engine::Engine()
                : monitors(nullptr),
                count(0)
            {
                if (!glfwInit())
                    throw std::runtime_error("Failure initializing GLFW");

                int c = 0;
                monitors = glfwGetMonitors(&c);

                count = c;
            }

            Engine::~Engine()
            {
                glfwTerminate();
            }

            uint32_t Engine::monitorCount() const
            {
                return count;
            }

            util::Size Engine::monitorVirtualPosition(uint32_t monitorIdx) const
            {
                int x = 0;
                int y = 0;

                glfwGetMonitorPos(get(monitorIdx), &x, &y);

                return{x, y};
            }

            util::Size Engine::monitorPhysicalSize(uint32_t monitorIdx) const
            {
                int x = 0;
                int y = 0;

                glfwGetMonitorPhysicalSize(get(monitorIdx), &x, &y);

                return{x, y};
            }

            VideoMode Engine::monitorCurrentMode(uint32_t monitorIdx) const
            {
                auto* mode = glfwGetVideoMode(get(monitorIdx));

                return {mode};
            }

            std::vector<VideoMode> Engine::monitorSupportedModes(uint32_t monitorIdx) const
            {
                int c = 0;
                auto* modes = glfwGetVideoModes(get(monitorIdx), &c);

                std::vector<VideoMode> ret;
                ret.reserve(c);

                for (int i = 0; i < c; ++i)
                    ret.emplace_back(static_cast<uint32_t>(modes[i].width),   static_cast<uint32_t>(modes[i].height),
                                     static_cast<uint32_t>(modes[i].redBits), static_cast<uint32_t>(modes[i].greenBits), static_cast<uint32_t>(modes[i].blueBits),
                                     static_cast<uint32_t>(modes[i].refreshRate));

                return ret;
            }

            std::string Engine::monitorName(uint32_t monitorIdx) const
            {
                return glfwGetMonitorName(get(monitorIdx));
            }

            GLFWmonitor* Engine::get(uint32_t idx) const
            {
                if (idx >= count)
                    throw std::runtime_error("Invalid monitor index");

                return monitors[idx];
            }
        }
	}
}
