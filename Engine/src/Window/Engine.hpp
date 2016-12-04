#ifndef DBR_GL_ENGINE_HPP
#define DBR_GL_ENGINE_HPP

#include <string>
#include <vector>

#include "util/Types.hpp"

struct GLFWmonitor;

namespace dbr
{
	namespace gl
	{
		struct VideoMode
		{
			VideoMode() = default;
			VideoMode(std::size_t width, std::size_t height, std::size_t redBits, std::size_t greenBits, std::size_t blueBits, std::size_t refreshRate);

			// size in screen coordinates
			std::size_t width;
			std::size_t height;

			// bit depths
			std::size_t redBits;
			std::size_t greenBits;
			std::size_t blueBits;

			// in Hz
			std::size_t refreshRate;
		};

		class Engine
		{
			friend class Window;

		public:
			~Engine();

			// the primary monitor is always index 0
			std::size_t monitorCount() const;

			// in screen-coordinates - does not correspond to pixels
			Size monitorVirtualPosition(std::size_t monitorIdx) const;

			// size in millimeters
			Size monitorPhysicalSize(std::size_t monitorIdx) const;

			VideoMode monitorCurrentMode(std::size_t monitorIdx) const;
			std::vector<VideoMode> monitorSupportedModes(std::size_t monitorIdx) const;
			std::string monitorName(std::size_t monitorIdx) const;

			static Engine instance;

		private:
			Engine();

			GLFWmonitor* get(std::size_t idx) const;

			GLFWmonitor** monitors;
			std::size_t count;
		};
	}
}

#endif
