#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

#define GLM_FORCE_LEFT_HANDED

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/rotate_vector.hpp>
#pragma warning(pop)

#include "Window/Engine.hpp"
#include "Window/Window.hpp"
#include "Graphics/BufferManager.hpp"
#include "Graphics/Program.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Uniform.hpp"

using namespace dbr;
using namespace std::chrono_literals;

int main(int, char**)
{
	bool run = true;

	gl::Window window;

	glm::mat4 model;
	model = glm::rotate(model, glm::radians(45.f), glm::vec3{1, 0, 0});

	glm::vec3 cameraPosition{0.f, 0.f, -10.f};
	glm::vec3 cameraFace{0.f, 0.f, 1.f};
	const glm::vec3 up{0.f, 1.f, 0.f};

	glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFace, up);
	
	glm::mat4 projection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.f);

	window.resized += [](int w, int h)
	{
		gl::Viewport(0, 0, w, h);
	};

	window.frameBufferResized += [&projection](int w, int h)
	{
		projection = glm::perspective(glm::radians(45.f), static_cast<float>(w) / h, 0.1f, 100.f);
	};

	bool moveForward = false;
	bool moveBackward = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool moveUp = false;
	bool moveDown = false;

	bool boost = false;

	window.key += [&](gl::Keyboard key, int scancode, gl::Events::Button action, gl::Modifiers mods)
	{
		bool act = action != gl::Events::Button::Release;

		int ikey = static_cast<int>(key);

		boost = (mods & gl::Modifiers::Shift) != gl::Modifiers::None;

		if(ikey == GLFW_KEY_W)
		{
			moveForward = act;
		}
		else if(ikey == GLFW_KEY_S)
		{
			moveBackward = act;
		}
		else if(ikey == GLFW_KEY_A)
		{
			moveLeft = act;
		}
		else if(ikey == GLFW_KEY_D)
		{
			moveRight = act;
		}
		else if(ikey == GLFW_KEY_R)
		{
			moveUp = act;
		}
		else if(ikey == GLFW_KEY_F)
		{
			moveDown = act;
		}
		else if(ikey == GLFW_KEY_ESCAPE)
		{
			run = false;
		}
		else
		{
			// nope
		}
	};

	bool firstMouse = true;
	glm::vec2 mouseLast{640, 360};
	
	float yaw = 0.f;
	float pitch = 0.f;

	window.mouseMoved += [&](double x, double y)
	{
		if(firstMouse)
		{
			mouseLast = {x, y};
			firstMouse = false;
			return;
		}

		glm::vec2 mouseNow{x, y};

		auto offset = mouseNow - mouseLast;
		offset.y *= -1;	// y-axis flipped

		mouseLast = mouseNow;

		constexpr float sensitivity = 0.25f;
		offset *= sensitivity;

		yaw += offset.x;
		pitch += offset.y;
		
		pitch = glm::max(-89.f, glm::min(89.f, pitch));

		auto yawRads = glm::radians(yaw);
		auto pitchRads = glm::radians(pitch);

		auto cosYaw = glm::cos(yawRads);
		auto cosPitch = glm::cos(pitchRads);
		auto sinYaw = glm::sin(yawRads);
		auto sinPitch = glm::sin(pitchRads);

		cameraFace.x = cosPitch * cosYaw;
		cameraFace.y = sinPitch;
		cameraFace.z = cosPitch * sinYaw;

		cameraFace = glm::normalize(cameraFace);

		std::cout << "<" << cameraFace.x << ", " << cameraFace.y << ", " << cameraFace.z << ">\n";
	};

	window.open(1280, 720, "OpenGL");
	window.lockCursor();

	gl::Program basicProgram;
	{
		gl::Shader basicVert(gl::Shader::Type::Vertex);
		gl::Shader basicFrag(gl::Shader::Type::Fragment);
		
		std::ifstream finBasicVert("shaders/basic.vert");
		std::ifstream finBasicFrag("shaders/basic.frag");

		basicVert.load(finBasicVert);
		basicFrag.load(finBasicFrag);

		basicProgram.link(basicVert, basicFrag);
	}

	gl::BufferManager bufferManager(gl::GenBuffers, gl::DeleteBuffers);
	gl::BufferManager arrayManager(gl::GenVertexArrays, gl::DeleteVertexArrays);

	bufferManager.request(1);
	arrayManager.request(1);

	gl::HandleU vbo = bufferManager.next();
	gl::HandleU vao = arrayManager.next();

	const float data[] =
	{
		// vertices		// colors
		-1, -1,  1,		1, 0, 0, 1,
		 1, -1,  1,		0, 1, 0, 1,
		-1,  1,  1,		0, 0, 1, 1,
		 1,  1,  1,		1, 1, 1, 1,
	};

	gl::BindVertexArray(vao);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, 0);
	gl::EnableVertexAttribArray(0);

	gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, reinterpret_cast<void*>(sizeof(float) * 3));
	gl::EnableVertexAttribArray(1);

	gl::Enable(gl::DEPTH_TEST);
	gl::Disable(gl::CULL_FACE);

	auto transform = basicProgram.getUniform("transform");
	
	using Tick = std::chrono::steady_clock::duration;

	// 60 ticks occur every second: cast to nanoseconds per tick
	constexpr Tick UPDATE_RATE = std::chrono::duration_cast<Tick>(std::chrono::duration<Tick::rep, std::ratio<1, 60>>{1});

	auto lastTime = std::chrono::steady_clock::now();
	Tick lag = Tick::zero();

	while(run)
	{
		auto nowTime = std::chrono::steady_clock::now();
		Tick frameTime = nowTime - lastTime;
		lastTime = nowTime;

		lag += frameTime;

		// Updating
		while(lag >= UPDATE_RATE)
		{
			window.pollEvents();

			constexpr float boostScale = 2.f;
			constexpr float moveAmt = 1.f;

			glm::ivec3 move{0, 0, 0};

			if(moveForward)
			{
				move.z += 1;
			}

			if(moveBackward)
			{
				move.z -= 1;
			}

			if(moveLeft)
			{
				move.x -= 1;
			}

			if(moveRight)
			{
				move.x += 1;
			}

			if(moveUp)
			{
				move.y += 1;
			}

			if(moveDown)
			{
				move.y -= 1;
			}
			
			auto fltMove = static_cast<glm::vec3>(move);

			if(glm::length(fltMove) != 0)
				cameraPosition += glm::normalize(fltMove) * moveAmt * (boost ? boostScale : 1.f);

			view = glm::lookAt(cameraPosition, cameraPosition + cameraFace, up);

			if(!window.isOpen())
				run = false;

			lag -= UPDATE_RATE;
		}

		// Drawing
		window.clear();

		transform.set(projection * view * model);
		basicProgram.use();

		gl::BindVertexArray(vao);
		{
			gl::DrawArrays(gl::TRIANGLE_STRIP, 0, 4);
		}
		gl::BindVertexArray(0);

		window.display();
	}

	window.close();

	return 0;
}
