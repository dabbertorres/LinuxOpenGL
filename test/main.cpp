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
#include "Math/Vector4.hpp"
//#include "Math/Quaternion.hpp"
//#include "Graphics/Color.hpp"

using namespace dbr;
using namespace std::chrono_literals;

int main(int, char**)
{
	bool run = true;

	gl::Window window;

	window.resized += [](int w, int h)
	{
		gl::Viewport(0, 0, w, h);
	};

	window.open(1280, 720, "OpenGL");

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
		// vertices			// colors
		+0.0, +1.0, +0.0,	1, 0, 0, 1,
		+1.0, +0.0, +0.0,	0, 1, 0, 1,
		-1.0, +0.0, +0.0,	0, 0, 1, 1,
		+0.0, -1.0, +0.0,	1, 1, 1, 1,
	};

	gl::BindVertexArray(vao);

	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, 0);
	gl::EnableVertexAttribArray(0);

	gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 7, reinterpret_cast<void*>(sizeof(float) * 3));
	gl::EnableVertexAttribArray(1);

	gl::Enable(gl::DEPTH_TEST);

	auto identity = math::Matrix4f::identity();

	basicProgram.getUniform("transform").set(identity);

	math::Vector4f v0{0, 1, 0};
	math::Vector4f v1{1, 0, 0};
	math::Vector4f v2{-1, 0, 0};
	math::Vector4f v3{0, -1, 0};

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

		// Updating
		while(lag >= UPDATE_RATE)
		{
			window.pollEvents();

			if(!window.isOpen())
				run = false;

			lag -= UPDATE_RATE;
		}

		// Drawing
		window.clear();

		basicProgram.use();

		gl::BindVertexArray(vao);
		{
			gl::DrawArrays(gl::TRIANGLE_STRIP, 0, 4);
		}
		gl::BindVertexArray(0);

		basicProgram.unuse();

		window.display();
	}

	window.close();

	return 0;
}
