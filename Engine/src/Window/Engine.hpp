#ifndef DBR_ENG_WINDOW_ENGINE_HPP
#define DBR_ENG_WINDOW_ENGINE_HPP

#include <string>
#include <vector>

#include "util/Types.hpp"

struct GLFWmonitor;
struct GLFWvidmode;

namespace dbr
{
	namespace eng
	{
        namespace win
        {
            struct VideoMode
            {
                VideoMode() = default;
                VideoMode(const GLFWvidmode* mode);
                VideoMode(uint32_t width, uint32_t height, uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t refreshRate);

                // size in screen coordinates
                uint32_t width;
                uint32_t height;

                // bit depths
                uint32_t redBits;
                uint32_t greenBits;
                uint32_t blueBits;

                // in Hz
                uint32_t refreshRate;
            };

            class Engine
            {
                friend class Window;

            public:
                ~Engine();

                // the primary monitor is always index 0
                uint32_t monitorCount() const;

                // in screen-coordinates - does not correspond to pixels
                util::Size monitorVirtualPosition(uint32_t monitorIdx) const;

                // size in millimeters
                util::Size monitorPhysicalSize(uint32_t monitorIdx) const;

                VideoMode monitorCurrentMode(uint32_t monitorIdx) const;
                std::vector<VideoMode> monitorSupportedModes(uint32_t monitorIdx) const;
                std::string monitorName(uint32_t monitorIdx) const;

                static Engine instance;

            private:
                Engine();

                GLFWmonitor* get(uint32_t idx) const;

                GLFWmonitor** monitors;
                uint32_t count;
            };
        }
	}
}

#endif
