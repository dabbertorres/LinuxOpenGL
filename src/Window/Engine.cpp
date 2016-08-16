#include "Engine.hpp"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "opengl/gl_glCore33.hpp"

namespace dbr
{
	namespace gl
	{
		VideoMode::VideoMode(std::size_t width, std::size_t height, std::size_t redBits, std::size_t greenBits, std::size_t blueBits, std::size_t refreshRate)
			: width(width),
			height(height),
			redBits(redBits),
			greenBits(greenBits),
			blueBits(blueBits),
			refreshRate(refreshRate)
		{}
		
		Engine Engine::instance;
		
		Engine::Engine()
			: monitors(nullptr),
			count(0)
		{
			if(!glfwInit())
				throw std::runtime_error("Failure initializing GLFW");

			int c = 0;
			monitors = glfwGetMonitors(&c);

			count = c;
		}

		Engine::~Engine()
		{
			glfwTerminate();
		}

		std::size_t Engine::monitorCount() const
		{
			return count;
		}

		Size Engine::monitorVirtualPosition(std::size_t monitorIdx) const
		{
			int x = 0;
			int y = 0;

			glfwGetMonitorPos(get(monitorIdx), &x, &y);

			return{static_cast<std::size_t>(x), static_cast<std::size_t>(y)};
		}

		Size Engine::monitorPhysicalSize(std::size_t monitorIdx) const
		{
			int x = 0;
			int y = 0;

			glfwGetMonitorPhysicalSize(get(monitorIdx), &x, &y);

			return{static_cast<std::size_t>(x), static_cast<std::size_t>(y)};
		}

		VideoMode Engine::monitorCurrentMode(std::size_t monitorIdx) const
		{
			auto* mode = glfwGetVideoMode(get(monitorIdx));

			return{static_cast<std::size_t>(mode->width), static_cast<std::size_t>(mode->height),
					static_cast<std::size_t>(mode->redBits), static_cast<std::size_t>(mode->greenBits), static_cast<std::size_t>(mode->blueBits),
					static_cast<std::size_t>(mode->refreshRate)};
		}

		std::vector<VideoMode> Engine::monitorSupportedModes(std::size_t monitorIdx) const
		{
			int c = 0;
			auto* modes = glfwGetVideoModes(get(monitorIdx), &c);

			std::vector<VideoMode> ret;
			ret.reserve(c);

			for(int i = 0; i < c; ++i)
				ret.emplace_back(static_cast<std::size_t>(modes[i].width), static_cast<std::size_t>(modes[i].height),
								 static_cast<std::size_t>(modes[i].redBits), static_cast<std::size_t>(modes[i].greenBits), static_cast<std::size_t>(modes[i].blueBits),
								 static_cast<std::size_t>(modes[i].refreshRate));

			return ret;
		}

		std::string Engine::monitorName(std::size_t monitorIdx) const
		{
			return glfwGetMonitorName(get(monitorIdx));
		}

		GLFWmonitor* Engine::get(std::size_t idx) const
		{
			if(idx >= count)
				throw std::runtime_error("Invalid monitor index");

			return monitors[idx];
		}
	}
}
