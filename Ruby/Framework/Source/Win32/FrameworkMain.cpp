#include "FrameworkPCH.h"
#include "FrameworkMain.h"

#include "InputManager.h"

#include "GLFW/glfw3.h"

Framework::Framework()
    : myWindow(nullptr)
    , m_pGameCore(nullptr)
    , m_InitialWindowWidth(-1)
    , m_InitialWindowHeight(-1)
    , m_CurrentWindowWidth(-1)
    , m_CurrentWindowHeight(-1)
{}

void Framework::Init(int width, int height)
{
    m_InitialWindowWidth = width;
    m_InitialWindowHeight = height;
    m_CurrentWindowWidth = m_InitialWindowWidth;
    m_CurrentWindowHeight = m_InitialWindowHeight;

    std::string title = "Ruby";
#if WIN32
    title.append(" Windows x86");
#else
    title.append(" Windows x64");
#endif

    if (!CreateGLWindow(title.c_str(), width, height))
        WindowsUtility::OutputMessage("Failed to initialize OpenGL window");
}

void Framework::Run(GameCore* pGameCore)
{
    m_pGameCore = pGameCore;
    m_pGameCore->OnSurfaceChanged(m_CurrentWindowWidth, m_CurrentWindowHeight);
    m_pGameCore->LoadContent();

    double previousTime = WindowsUtility::GetSystemTime();

    while (!glfwWindowShouldClose(myWindow))
    {
        glfwPollEvents();

        if (InputManager::GetInstance().IsKeyDown(Keys::Escape))
            glfwSetWindowShouldClose(myWindow, true);

        const double currentTime = WindowsUtility::GetSystemTime();
        const float deltaTime = static_cast<float>(currentTime - previousTime);
        previousTime = currentTime;

        m_pGameCore->GetEventManager()->DispatchEvents(m_pGameCore);
        m_pGameCore->Update(deltaTime);
        m_pGameCore->Draw();
        glfwGetFramebufferSize(myWindow, &m_CurrentWindowWidth, &m_CurrentWindowHeight);
        glfwSwapBuffers(myWindow);
    }
}

void Framework::Shutdown() const
{
    KillGLWindow();
}

void Framework::SetWindowSize(int width, int height)
{
    const int maxWidth = 720;
    const int maxHeight = 480;
    const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

    int nextWidth = width;
    int nextHeight = height;

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

void Framework::ResizeWindow(int width, int height)
{
    if (height <= 0)
        height = 1;

    if (width <= 0)
        width = 1;

    m_CurrentWindowWidth = width;
    m_CurrentWindowHeight = height;

    if (m_pGameCore)
        m_pGameCore->OnSurfaceChanged(width, height);
}

bool Framework::CreateGLWindow(const char* title, int width, int height)
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

    myWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
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

    ResizeWindow(width, height);

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
