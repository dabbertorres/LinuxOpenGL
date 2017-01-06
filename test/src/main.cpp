#include <chrono>
#include <fstream>
#include <thread>

#include "Window/Window.hpp"
#include "Math/Math.hpp"
#include "Graphics/BufferManager.hpp"
#include "Graphics/Program.hpp"
#include "Graphics/Shader.hpp"
#include "Graphics/Uniform.hpp"

#define INVERT_MOUSE_Y

using namespace dbr::eng;

int main(int argc, char** argv)
{
    std::uint32_t windowWidth  = 1280;
    std::uint32_t windowHeight = 720;

    float aspectRatio = static_cast<float>(windowWidth) / windowHeight;
    float verticalFOV = glm::quarter_pi<float>();

    auto calcProjMat = [&]() { return glm::perspective(verticalFOV, aspectRatio, 1.f, 100.f); };

    gfx::HandleU crosshairVBO;
    gfx::HandleU crosshairVAO;

    auto makeCrosshair = [&]()
    {
        gl::BindVertexArray(crosshairVAO);
        {
            float data[] =
            {
                // vertices    // colors
                -1,  0, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
                 1,  0, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
                 0, -1, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
                 0,  1, 0, 1,  0.7f, 0.7f, 0.7f, 0.7f,
            };

            data[0] *= 1.f / aspectRatio;
            data[8] *= 1.f / aspectRatio;

            gl::BindBuffer(gl::ARRAY_BUFFER, crosshairVBO);
            gl::BufferData(gl::ARRAY_BUFFER, sizeof(data), data, gl::STATIC_DRAW);

            gl::VertexAttribPointer(0, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, nullptr);
            gl::EnableVertexAttribArray(0);

            gl::VertexAttribPointer(1, 4, gl::FLOAT, gl::FALSE_, sizeof(float) * 8, reinterpret_cast<void*>(sizeof(float) * 4));
            gl::EnableVertexAttribArray(1);
        }
        gl::BindVertexArray(0);
    };

    bool run = true;

    constexpr glm::vec3 cameraInitialPosition{0.f, 0.f, -10.f};
    constexpr glm::vec3 cameraInitialFace{0.f, 0.f, 1.f};
    constexpr glm::vec3 cameraInitialUp{0.f, 1.f, 0.f};

    float yaw   = 0.f;
    float pitch = 0.f;
    float roll  = glm::half_pi<float>();

    glm::vec3 cameraPosition = cameraInitialPosition;
    glm::vec3 cameraFace     = cameraInitialFace;
    glm::vec3 cameraUp       = cameraInitialUp;

    glm::mat4 view       = glm::lookAt(cameraPosition, cameraPosition + cameraFace, cameraUp);
    glm::mat4 projection = calcProjMat();

    glm::mat4 targetModel = glm::rotate(glm::mat4{}, glm::quarter_pi<float>(), glm::vec3{0, 0, 1});

//    glm::quat cameraRotation = glm::angleAxis(0.f, cameraFace);

    win::Window window;

    window.resized += [](int w, int h)
    {
        gl::Viewport(0, 0, w, h);
    };

    window.frameBufferResized += [&](int w, int h)
    {
        aspectRatio = static_cast<float>(w) / h;
        projection = calcProjMat();
        makeCrosshair();
    };

    bool moveForward  = false;
    bool moveBackward = false;
    bool moveLeft     = false;
    bool moveRight    = false;
    bool moveUp       = false;
    bool moveDown     = false;
    bool rotateCW     = false;
    bool rotateCCW    = false;

    bool boost = false;

    bool mouseMoved = false;

    window.key += [&](win::Keyboard key, int /*scancode*/, win::Events::Button action, win::Modifiers mods)
    {
        bool act = action != win::Events::Button::Release;

        boost = (mods & win::Modifiers::Shift) != win::Modifiers::None;

        switch (key)
        {
            case win::Keyboard::W:
                moveForward = act;
                break;

            case win::Keyboard::S:
                moveBackward = act;
                break;

            case win::Keyboard::A:
                moveLeft = act;
                break;

            case win::Keyboard::D:
                moveRight = act;
                break;

            case win::Keyboard::R:
                moveUp = act;
                break;

            case win::Keyboard::F:
                moveDown = act;
                break;

            case win::Keyboard::Q:
                rotateCCW = act;
                break;

            case win::Keyboard::E:
                rotateCW = act;
                break;

            case win::Keyboard::Escape:
                run = false;
                break;

            default:
                // nope
                break;
        }
    };

    glm::vec2 mouseLast{windowWidth / 2, windowHeight / 2};
    glm::vec2 mouseNow = mouseLast;

    window.mouseMoved += [&](double x, double y)
    {
        mouseNow = {x, y};
        mouseMoved = true;
    };

    window.open(windowWidth, windowHeight, "OpenGL");
    window.lockCursor();

    gfx::Program basicProgram;
    {
        gfx::Shader basicVert(gfx::Shader::Type::Vertex);
        gfx::Shader basicFrag(gfx::Shader::Type::Fragment);

        std::ifstream finBasicVert("shaders/basic.vert");
        std::ifstream finBasicFrag("shaders/basic.frag");

        basicVert.load(finBasicVert);
        basicFrag.load(finBasicFrag);

        basicProgram.link(basicVert, basicFrag);
    }

    gl::Enable(gl::DEPTH_TEST);
//	gl::Disable(gl::CULL_FACE);

    gfx::BufferManager bufferManager(gl::GenBuffers, gl::DeleteBuffers);
    gfx::BufferManager arrayManager(gl::GenVertexArrays, gl::DeleteVertexArrays);

    bufferManager.request(2);
    arrayManager.request(2);

    gfx::HandleU squareVBO = bufferManager.next();
    gfx::HandleU squareVAO = arrayManager.next();

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

    crosshairVBO = bufferManager.next();
    crosshairVAO = arrayManager.next();

    makeCrosshair();

    auto transform = basicProgram.getUniform("transform");

    using Tick = std::chrono::steady_clock::duration;

    // 60 ticks occur every second: cast to nanoseconds per tick
    constexpr Tick DT = std::chrono::duration_cast<Tick>(std::chrono::duration<Tick::rep, std::ratio<1, 60>>{1});
    constexpr auto DT_SEC = DT.count() / static_cast<float>(std::chrono::nanoseconds{std::chrono::seconds{1}}.count());

    auto lastTime = std::chrono::steady_clock::now();
    Tick lag = Tick::zero();

    while (run)
    {
        auto nowTime   = std::chrono::steady_clock::now();
        Tick frameTime = nowTime - lastTime;
        lastTime       = nowTime;

        lag += frameTime;

        // Updating
        while (lag >= DT)
        {
            window.pollEvents();

            // 0.25 seems to work well
            constexpr float MOUSE_SENSITIVITY = 0.25f;
            constexpr float BOOST_SPEED       = 4.f;
            constexpr float MOVE_SPEED        = 2.f;
            constexpr float ROLL_SPEED        = glm::quarter_pi<float>();

            // a little less than 90 deg
            constexpr float MAX_PITCH = glm::half_pi<float>() * 0.98f;
            constexpr float MIN_PITCH = -MAX_PITCH;

            // TODO
            // rotation is funny.
            // yaw/pitch are not respecting the roll. Lel.
            // may be time to dig into quaternions

            // yaw/pitch
            if (mouseMoved)
            {
                auto offset = mouseNow - mouseLast;

                mouseLast = mouseNow;
                offset *= MOUSE_SENSITIVITY;

                yaw   += glm::radians(offset.x);
                pitch += glm::radians(offset.y);

                pitch = glm::max(MIN_PITCH, glm::min(MAX_PITCH, pitch));

                auto cosYaw   = glm::cos(yaw);
                auto cosPitch = glm::cos(pitch);
                auto sinYaw   = glm::sin(yaw);
                auto sinPitch = glm::sin(pitch);

                cameraFace.x = cosPitch * sinYaw;
                cameraFace.z = cosPitch * cosYaw;

#ifndef INVERT_MOUSE_Y
                cameraFace.y = -sinPitch;
#else
                cameraFace.y = sinPitch;
#endif

                cameraFace = glm::normalize(cameraFace);

                mouseMoved = false;
            }

            // roll
            {
                if (rotateCW)
                    roll -= ROLL_SPEED * DT_SEC;

                if (rotateCCW)
                    roll += ROLL_SPEED * DT_SEC;

                cameraUp.x = std::cos(roll);
                cameraUp.y = std::sin(roll);
            }

            // movement
            {
                const glm::vec3 cameraFaceRight{cameraFace.z, cameraFace.y, -cameraFace.x};
                const glm::vec3 cameraFaceUp{cameraFace.x, cameraFace.z, -cameraFace.y};

                glm::vec3 dir{0, 0, 0};

                if (moveForward)
                    dir += cameraFace;

                if (moveBackward)
                    dir -= cameraFace;

                if (moveRight)
                    dir += cameraFaceRight;

                if (moveLeft)
                    dir -= cameraFaceRight;

                if (moveUp)
                    dir += cameraFaceUp;

                if (moveDown)
                    dir -= cameraFaceUp;

                if (glm::length(dir) != 0)
                    cameraPosition += glm::normalize(dir) * (boost ? BOOST_SPEED : MOVE_SPEED) * DT_SEC;
            }

            view = glm::lookAt(cameraPosition, cameraPosition + cameraFace, cameraUp);

            if (!window.isOpen())
                run = false;

            lag -= DT;
        }

        // Drawing
        window.clear();

        basicProgram.use();

        transform.set(projection * view * targetModel);
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
