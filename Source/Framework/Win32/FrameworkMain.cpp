#include "FrameworkMain.h"

#include <chrono>
#include <string>

#include "Events/EventManager.h"
#include "GameCore/GameCore.h"
#include "GL/GLHelpers.h"
#include "GLFW/glfw3.h"
#include "Input/InputManager.h"
#include "Utility/DebugUtility.h"

Framework::Framework()
    : myWindow(nullptr)
    , myGameCore(nullptr)
    , myInitialWindowWidth(-1)
    , myInitialWindowHeight(-1)
    , myCurrentWindowWidth(-1)
    , myCurrentWindowHeight(-1)
{}

void Framework::Init(int aWidth, int aHeight)
{
    myInitialWindowWidth = aWidth;
    myInitialWindowHeight = aHeight;
    myCurrentWindowWidth = myInitialWindowWidth;
    myCurrentWindowHeight = myInitialWindowHeight;

    std::string title = "Ruby";
#if _WIN64
    title.append(" Windows x64");
#elif _WIN32
    title.append(" Windows x86");
#endif

    if (!CreateWindow(title.c_str(), aWidth, aHeight))
        DebugUtility::OutputMessage("Failed to initialize OpenGL window");

    PrintDebugInfo();
}

void Framework::Run(GameCore* aGameCore)
{
    myGameCore = aGameCore;
    myGameCore->OnSurfaceChanged(myCurrentWindowWidth, myCurrentWindowHeight);
    myGameCore->LoadContent();

    auto previousTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(myWindow))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = currentTime - previousTime;
        const float deltaTime = std::chrono::duration<float>(elapsedTime).count();
        previousTime = currentTime;

        glfwPollEvents();

        if (InputManager::GetInstance().IsKeyDown(Keys::Escape))
            glfwSetWindowShouldClose(myWindow, true);

        myGameCore->GetEventManager()->DispatchEvents(myGameCore);
        myGameCore->Update(deltaTime);
        myGameCore->Draw();
        glfwGetFramebufferSize(myWindow, &myCurrentWindowWidth, &myCurrentWindowHeight);
        glfwSwapBuffers(myWindow);
    }
}

void Framework::Shutdown() const
{
    KillGLWindow();
}

void Framework::SetWindowSize(int aWidth, int aHeight)
{
    const int maxWidth = 720;
    const int maxHeight = 480;
    const float aspectRatio = static_cast<float>(aWidth) / static_cast<float>(aHeight);

    int nextWidth = aWidth;
    int nextHeight = aHeight;

    if (nextWidth > maxWidth)
    {
        nextWidth = maxWidth;
        nextHeight = static_cast<int>(static_cast<float>(maxWidth) / aspectRatio);
    }

    if (nextHeight > maxHeight)
    {
        nextWidth = static_cast<int>(static_cast<float>(maxHeight) * aspectRatio);
        nextHeight = maxHeight;
    }

    ResizeWindow(nextWidth, nextHeight);
}

void Framework::SetWindowIcon(unsigned char* aSource, int aWidth, int aHeight) const
{
    GLFWimage processIcon[1];
    processIcon[0].pixels = aSource;
    processIcon[0].width = aWidth;
    processIcon[0].height = aHeight;
    glfwSetWindowIcon(myWindow, 1, processIcon);
}

void Framework::PrintDebugInfo() const
{
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    DebugUtility::OutputMessage("GLFW %i.%i.%i", major, minor, revision);
    DebugUtility::OutputMessage("OpenGL %s", glGetString(GL_VERSION));
    DebugUtility::OutputMessage("Vendor %s", glGetString(GL_VENDOR));
    DebugUtility::OutputMessage("Renderer %s", glGetString(GL_RENDERER));
    DebugUtility::OutputMessage("GLSL %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

     int xPosition, yPosition;
    glfwGetWindowPos(myWindow, &xPosition, &yPosition);
    DebugUtility::OutputMessage("Window position %i %i", xPosition, yPosition);

    int width, height;
    glfwGetFramebufferSize(myWindow, &width, &height);
    DebugUtility::OutputMessage("Frame buffer size %i %i", width, height);

    float xScale, yScale;
    glfwGetWindowContentScale(myWindow, &xScale, &yScale);
    DebugUtility::OutputMessage("Window content scale %.1f %.1f", xScale, yScale);

    int left, top, right, bottom;
    glfwGetWindowFrameSize(myWindow, &left, &top, &right, &bottom);
    DebugUtility::OutputMessage("Window Frame size %i %i %i %i", left, top, right, bottom);

    DebugUtility::OutputMessage("Window size %ix%i", myCurrentWindowWidth, myCurrentWindowHeight);
}

void Framework::ResizeWindow(int aWidth, int aHeight)
{
    if (aHeight <= 0)
        aHeight = 1;

    if (aWidth <= 0)
        aWidth = 1;

    myCurrentWindowWidth = aWidth;
    myCurrentWindowHeight = aHeight;

    if (myGameCore)
        myGameCore->OnSurfaceChanged(aWidth, aHeight);
}

bool Framework::CreateWindow(const char* aTitle, int aWidth, int aHeight)
{
    glfwSetErrorCallback(GLHelpers::GLFWErrorCallback);

    if (!glfwInit())
    {
        glfwTerminate();
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    myWindow = glfwCreateWindow(aWidth, aHeight, aTitle, nullptr, nullptr);
    if (!myWindow)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(myWindow);
    glfwSetWindowUserPointer(myWindow, this);
    glfwSetKeyCallback(myWindow, KeyCallback);
    glfwSetInputMode(myWindow, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPosCallback(myWindow, CursorCallback);
    glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(myWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetScrollCallback(myWindow, ScrollCallback);
    glfwSetMouseButtonCallback(myWindow, MouseButtonCallback);

    ResizeWindow(aWidth, aHeight);

    if (!gladLoadGL())
        return false;

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GLHelpers::GLDebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Framework::KillGLWindow() const
{
    glfwDestroyWindow(myWindow);
    glfwTerminate();
}

void Framework::KeyCallback(GLFWwindow* /*aWindow*/, int aKey, int aScancode, int anAction, int aMode)
{
    InputManager::GetInstance().OnKeyAction(aKey, aScancode, anAction != GLFW_RELEASE, aMode);
}

void Framework::CursorCallback(GLFWwindow* /*aWindow*/, double aXPosition, double aYPosition)
{
    InputManager::GetInstance().OnCursorAction(aXPosition, aYPosition);
}

void Framework::ScrollCallback(GLFWwindow* /*aWindow*/, double aXOffset, double aYOffset)
{
    InputManager::GetInstance().OnScrollAction(aXOffset, aYOffset);
}

void Framework::MouseButtonCallback(GLFWwindow* /*aWindow*/, int aButton, int anAction, int aModifiers)
{
    InputManager::GetInstance().OnMouseButtonAction(aButton, anAction, aModifiers);
}
