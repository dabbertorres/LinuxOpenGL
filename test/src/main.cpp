#include <chrono>
#include <fstream>
#include <thread>

#include "Window/Window.hpp"
#include "Graphics/BufferManager.hpp"
#include "Graphics/Program.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Uniform.hpp"

#define INVERT_MOUSE_Y

using namespace dbr;

int main(int, char**)
{
    constexpr auto WIN_WIDTH = 1280u;
    constexpr auto WIN_HEIGHT = 720u;

    bool run = true;

    gl::Window window;

    glm::mat4 model;
    model = glm::rotate(model, glm::quarter_pi<float>(), glm::vec3{0, 0, 1});

    glm::vec3 cameraPosition{0.f, 0.f, -10.f};
    glm::vec3 cameraFace{0.f, 0.f, 1.f};
    glm::vec3 cameraUp{0.f, 1.f, 0.f};

    glm::quat cameraRotation = glm::angleAxis(0.f, cameraFace);

    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFace, cameraUp);
    glm::mat4 projection = glm::perspective(glm::quarter_pi<float>(), WIN_WIDTH / static_cast<float>(WIN_HEIGHT), 1.f, 100.f);

    window.resized += [](int w, int h)
    {
        gl::Viewport(0, 0, w, h);
    };

    window.frameBufferResized += [&projection](int w, int h)
    {
        projection = glm::perspective(glm::half_pi<float>(), static_cast<float>(w) / h, 1.f, 100.f);
    };

    bool moveForward = false;
    bool moveBackward = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveUp = false;
    bool moveDown = false;

    bool boost = false;

    window.key += [&](gl::Keyboard key, int /*scancode*/, gl::Events::Button action, gl::Modifiers mods)
    {
        bool act = action != gl::Events::Button::Release;

        boost = (mods & gl::Modifiers::Shift) != gl::Modifiers::None;

        switch(key)
        {
            case gl::Keyboard::W:
                moveForward = act;
                break;

            case gl::Keyboard::S:
                moveBackward = act;
                break;

            case gl::Keyboard::A:
                moveLeft = act;
                break;

            case gl::Keyboard::D:
                moveRight = act;
                break;

            case gl::Keyboard::R:
                moveUp = act;
                break;

            case gl::Keyboard::F:
                moveDown = act;
                break;

            case gl::Keyboard::Escape:
                run = false;
                break;

            default:
                // nope
                break;
        }
    };

    bool firstMouse = true;
    glm::vec2 mouseLast{WIN_WIDTH / 2, WIN_HEIGHT / 2};

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

        mouseLast = mouseNow;

        // 0.25 seems to work well
        constexpr float sensitivity = 0.25f;
        offset *= sensitivity;

        yaw += glm::radians(offset.x);
        pitch += glm::radians(offset.y);

        // a little less than 90 deg
        constexpr auto MAX_PITCH = glm::half_pi<float>() * 0.98f;
        constexpr auto MIN_PITCH = -MAX_PITCH;

        pitch = glm::max(MIN_PITCH, glm::min(MAX_PITCH, pitch));

        auto cosYaw = glm::cos(yaw);
        auto cosPitch = glm::cos(pitch);
        auto sinYaw = glm::sin(yaw);
        auto sinPitch = glm::sin(pitch);

        cameraFace.x = cosPitch * sinYaw;
        cameraFace.z = cosPitch * cosYaw;

#ifndef INVERT_MOUSE_Y
        cameraFace.y = -sinPitch;
#else
        cameraFace.y = sinPitch;
#endif

        cameraFace = glm::normalize(cameraFace);
    };

    window.open(WIN_WIDTH, WIN_HEIGHT, "OpenGL");
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

    gl::Enable(gl::DEPTH_TEST);
//	gl::Disable(gl::CULL_FACE);

    gl::BufferManager bufferManager(gl::GenBuffers, gl::DeleteBuffers);
    gl::BufferManager arrayManager(gl::GenVertexArrays, gl::DeleteVertexArrays);

    bufferManager.request(2);
    arrayManager.request(2);

    gl::HandleU squareVBO = bufferManager.next();
    gl::HandleU squareVAO = arrayManager.next();

    gl::BindVertexArray(squareVAO);
    {
        constexpr float data[] =
        {
            // vertices	   // colors
            -1, -1, 0, 1,  1, 0, 0, 1,
             1, -1, 0, 1,  0, 1, 0, 1,
            -1,  1, 0, 1,  0, 0, 1, 1,
             1,  1, 0, 1,  1, 1, 1, 1,
        };

        gl::BindBuffer(gl::ARRAY_BUFFER, squareVBO);
        gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

        gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, nullptr);
        gl::EnableVertexAttribArray(0);

        gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 4));
        gl::EnableVertexAttribArray(1);
    }
    gl::BindVertexArray(0);

    gl::HandleU crosshairVBO = bufferManager.next();
    gl::HandleU crosshairVAO = arrayManager.next();

    gl::BindVertexArray(crosshairVAO);
    {
        constexpr float data[] =
        {
            // vertices    // colors
            -1,  0, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
             1,  0, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
             0, -1, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
             0,  1, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
        };

        gl::BindBuffer(gl::ARRAY_BUFFER, crosshairVBO);
        gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

        gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, nullptr);
        gl::EnableVertexAttribArray(0);

        gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 4));
        gl::EnableVertexAttribArray(1);
    }
    gl::BindVertexArray(0);

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

            const glm::vec3 cameraFaceRight{cameraFace.z, cameraFace.y, -cameraFace.x};
            const glm::vec3 cameraFaceUp{cameraFace.x, cameraFace.z, -cameraFace.y};

            glm::vec3 move{0, 0, 0};

            if(moveForward)
                move += cameraFace;

            if(moveBackward)
                move -= cameraFace;

            if(moveRight)
                move += cameraFaceRight;

            if(moveLeft)
                move -= cameraFaceRight;

            if(moveUp)
                move += cameraFaceUp;

            if(moveDown)
                move -= cameraFaceUp;

            if(glm::length(move) != 0)
                cameraPosition += glm::normalize(move) * moveAmt * (boost ? boostScale : 1.f);

            view = glm::lookAt(cameraPosition, cameraPosition + cameraFace, cameraUp);

            if(!window.isOpen())
                run = false;

            lag -= UPDATE_RATE;
        }

        // Drawing
        window.clear();

        basicProgram.use();

        transform.set(projection * view * model);
        gl::BindVertexArray(squareVAO);
        gl::DrawArrays(gl::TRIANGLE_STRIP, 0, 4);

        transform.set(glm::scale(glm::mat4{}, glm::vec3{0.1f}));
        gl::BindVertexArray(crosshairVAO);
        gl::DrawArrays(gl::LINES, 0, 4);

        gl::BindVertexArray(0);

        window.display();
    }

    window.close();

    return 0;
}
