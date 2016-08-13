#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>

#include "Engine.hpp"
#include "Window/Window.hpp"
#include "BufferManager.hpp"
#include "Graphics/Program.hpp"
#include "Graphics/Shader.hpp"
#include "Uniform.hpp"
//#include "Math/Vector3.hpp"
//#include "Math/Quaternion.hpp"
//#include "Graphics/Color.hpp"

using namespace dbr;
using namespace std::chrono_literals;

int main(int, char**)
{
	bool run = true;

	gl::Window window;

	window.open(1280, 720, "OpenGL");

//	window.mouseMove += [](double x, double y)
//	{
//		std::cout << "mouse: (" << x << ' ' << y << ")\n";
//	};

	gl::Shader basicVert(gl::Shader::Type::Vertex);
	gl::Shader basicFrag(gl::Shader::Type::Fragment);

	gl::Shader texturedVert(gl::Shader::Type::Vertex);
	gl::Shader texturedFrag(gl::Shader::Type::Fragment);

	{
		std::ifstream finBasicVert("shaders/basic.vert");
		std::ifstream finBasicFrag("shaders/basic.frag");
		std::ifstream finTexVert("shaders/textured.vert");
		std::ifstream finTexFrag("shaders/textured.frag");

		basicVert.load(finBasicVert);
		basicFrag.load(finBasicFrag);
		texturedVert.load(finTexVert);
		texturedFrag.load(finTexFrag);
	}

	gl::Program basicProgram;
	gl::Program texturedProgram;

	basicProgram.link(basicVert, basicFrag);
	texturedProgram.link(texturedVert, texturedFrag);

	gl::BufferManager bufferManager(gl::GenBuffers, gl::DeleteBuffers);
	gl::BufferManager arrayManager(gl::GenVertexArrays, gl::DeleteVertexArrays);

	bufferManager.request(1);
	arrayManager.request(1);

	gl::HandleU buf = bufferManager.next();
	gl::HandleU arr = arrayManager.next();

	float data[] =
	{
		// vertices			// colors
		-0.5,	-0.5,	0,	1, 1, 1, 1,
		0,		 0.5,	0,	1, 1, 1, 1,
		0.5,	-0.5,	0,	1, 1, 1, 1,
	};

	gl::BindVertexArray(arr);
	{
		gl::BindBuffer(gl::ARRAY_BUFFER, buf);
		gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

		gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, nullptr);
		gl::EnableVertexAttribArray(0);

		gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, nullptr);
		gl::EnableVertexAttribArray(1);
	}
	gl::BindVertexArray(0);

	using Tick = std::chrono::steady_clock::duration;

	// 60 ticks occur every second: cast to nanoseconds between ticks
	constexpr Tick UPDATE_RATE = std::chrono::duration_cast<Tick>(std::chrono::duration<Tick::rep, std::ratio<1, 60>>{1});

	auto lastTime = std::chrono::steady_clock::now();

	Tick lag = Tick::zero();

	while(run)
	{
		auto nowTime = std::chrono::steady_clock::now();
		Tick frameTime = nowTime - lastTime;
		lastTime = nowTime;

		lag += frameTime;

		while(lag >= UPDATE_RATE)
		{
			// Events
			window.update();

			if(!window.isOpen())
				run = false;

			// other updating


			lag -= UPDATE_RATE;
		}

		// Drawing
		window.clear();

		basicProgram.use();

		gl::BindVertexArray(arr);
		{
			gl::DrawArrays(gl::TRIANGLES, 0, 1);
		}
		gl::BindVertexArray(0);

		window.display();
	}

	return 0;
}
