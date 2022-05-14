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
    , m_FullscreenMode(false)
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

    if (!CreateGLWindow(title.c_str(), width, height, 32, 31, 1, false))
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

bool Framework::CreateGLWindow(const char* title, int width, int height, char colorbits, char zbits, char stencilbits, bool fullscreenflag)
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

    m_FullscreenMode = fullscreenflag;

    //GLuint PixelFormat;

    //WNDCLASS wc;
    //DWORD dwExStyle;
    //DWORD dwStyle;

    //RECT WindowRect;
    //WindowRect.left = static_cast<long>(0);
    //WindowRect.right = static_cast<long>(width);
    //WindowRect.top = static_cast<long>(0);
    //WindowRect.bottom = static_cast<long>(height);

    //m_FullscreenMode = fullscreenflag;

    //m_hInstance = GetModuleHandle( 0 );             // Grab an instance for our window
    //wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw on move, and own dc for window
    //wc.lpfnWndProc = static_cast<WNDPROC>(WndProc);              // Wndproc handles messages
    //wc.cbClsExtra = 0;                              // No extra window data
    //wc.cbWndExtra = 0;                              // No extra window data
    //wc.hInstance = m_hInstance;                     // Set the instance
    //wc.hIcon = LoadIcon( 0, IDI_WINLOGO );          // Load the default icon
    //wc.hCursor = LoadCursor( 0, IDC_ARROW );        // Load the arrow pointer
    //wc.hbrBackground = 0;                           // No background required for GL
    //wc.lpszMenuName = 0;                            // We don't want a menu
    //wc.lpszClassName = "OpenGL";                    // Set the class name

    //if (!RegisterClass(&wc))                     // Attempt to register the window class
    //{
    //    MessageBox(nullptr, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //if (m_FullscreenMode)
    //{
    //    DEVMODE dmScreenSettings = {};                                   // Device mode
    //    dmScreenSettings.dmSize = sizeof( dmScreenSettings );       // Size of the devmode structure
    //    dmScreenSettings.dmPelsWidth = width;                      // Selected screen width
    //    dmScreenSettings.dmPelsHeight = height;                     // Selected screen height
    //    dmScreenSettings.dmBitsPerPel = colorbits;                  // Selected bits per pixel
    //    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    //    // Try to set selected mode and get results.  NOTE: CDS_FULLSCREEN gets rid of start bar.
    //    if (ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
    //    {
    //        // If the mode fails, offer two options.  Quit or run in a window.
    //        if( MessageBox(nullptr, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
    //        {
    //            m_FullscreenMode = false;
    //        }
    //        else
    //        {
    //            MessageBox(nullptr, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
    //            return false;
    //        }
    //    }
    //}

    //if( m_FullscreenMode )
    //{
    //    dwExStyle = WS_EX_APPWINDOW;
    //    dwStyle = WS_POPUP;
    //    ShowCursor(false);
    //}
    //else
    //{
    //    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    //    dwStyle = WS_OVERLAPPEDWINDOW;
    //}

    //AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );   // Adjust window to true requested size

    //if (!( CreateWindowEx(dwExStyle,           // Extended style for the window
    //    "OpenGL",                               // Class name
    //    title,                                  // Window title
    //    WS_CLIPSIBLINGS | WS_CLIPCHILDREN |     // Required window style
    //    dwStyle,                                // Selected window style
    //    0, 0,                                   // Window position
    //    WindowRect.right-WindowRect.left,       // Calculate adjusted window width
    //    WindowRect.bottom-WindowRect.top,       // Calculate adjusted window height
    //    nullptr,                                      // No parent window
    //    nullptr,                                      // No menu
    //    m_hInstance,                            // Instance
    //    this)))                                 // Pass a pointer to this framework object to WM_NCCREATE
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //PIXELFORMATDESCRIPTOR pfd = // pfd tells Windows how we want things to be
    //{
    //    sizeof(PIXELFORMATDESCRIPTOR),  // Size of this pixel format descriptor
    //    1,                              // Version number
    //    PFD_DRAW_TO_WINDOW |            // Format must support window
    //    PFD_SUPPORT_OPENGL |            // Format must support opengl
    //    PFD_DOUBLEBUFFER,               // Must support double buffering
    //    PFD_TYPE_RGBA,                  // Request an rgba format
    //    static_cast<BYTE>(colorbits),                // Select our color depth
    //    0, 0, 0, 0, 0, 0,               // Color bits ignored
    //    0,                              // No alpha buffer
    //    0,                              // Shift bit ignored
    //    0,                              // No accumulation buffer
    //    0, 0, 0, 0,                     // Accumulation bits ignored
    //    static_cast<BYTE>(zbits),                    // Bits for z-buffer (depth buffer)
    //    static_cast<BYTE>(stencilbits),              // Stencil bits
    //    0,                              // No auxiliary buffer
    //    PFD_MAIN_PLANE,                 // Main drawing layer
    //    0,                              // Reserved
    //    0, 0, 0                         // Layer masks ignored
    //};

    //if (!(m_hDeviceContext = GetDC( m_hWnd))) // Did we get a device context?
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //if( !( PixelFormat = ChoosePixelFormat( m_hDeviceContext, &pfd ) ) ) // Did Windows find a matching pixel format?
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //if( !SetPixelFormat( m_hDeviceContext, PixelFormat, &pfd ) ) // Are we able to set the pixel format?
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //if( !( m_hRenderingContext = wglCreateContext( m_hDeviceContext ) ) ) // Are we able to get a rendering context?
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //if( !wglMakeCurrent( m_hDeviceContext, m_hRenderingContext ) ) // Try to activate the rendering context.
    //{
    //    KillGLWindow();
    //    MessageBox(nullptr, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    //    return false;
    //}

    //ShowWindow(m_hWnd, SW_SHOW);   // Show the window.
    //SetForegroundWindow(m_hWnd);   // Slightly higher priority.
    //SetFocus(m_hWnd);              // Sets keyboard focus to the window.
    ResizeWindow(width, height); // Tells our GameCore object the window size.

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
    if (m_FullscreenMode)
        ShowCursor(true);

    glfwDestroyWindow(myWindow);
	glfwTerminate();
}

// This is a static method for gamerz.
//LRESULT CALLBACK Framework::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    // Get a pointer to the framework object associated with this window.
//    Framework* pFramework = (Framework*)GetWindowLongPtr( hWnd, GWLP_USERDATA );
//
//    switch(uMsg)
//    {
//        case WM_NCCREATE:
//        {
//            // Set the user data for this hWnd to the Framework* we passed in, used on first line of this method above.
//            CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
//            Framework* pFramework = (Framework*)pcs->lpCreateParams;
//            SetWindowLongPtr( hWnd, GWLP_USERDATA, (LONG)pFramework );
//
//            pFramework->m_hWnd = hWnd;
//            return 1;
//        }
//        case WM_DESTROY:
//        {
//            pFramework->m_hWnd = 0;
//            return 0;
//        }
//        case WM_ACTIVATE:
//        {
//            if( !HIWORD(wParam) )
//            {
//                pFramework->m_WindowIsActive = true;
//            }
//            else
//            {
//                pFramework->m_WindowIsActive = false;
//            }
//            return 0;
//        }
//        case WM_SYSCOMMAND:
//        {
//            switch( wParam )
//            {
//                // Don't let screensaver or monitor power save mode kick in.
//                case SC_SCREENSAVE:
//                case SC_MONITORPOWER:
//                    return 0;
//                default:
//                    break;
//            }
//            break;
//        }
//        case WM_CLOSE:
//        {
//            PostQuitMessage(0);
//            return 0;
//        }
//        case WM_KEYDOWN:
//        {
//            const bool keyWasPressedLastTimeMessageArrived = lParam & (1 << 30);
//            if( keyWasPressedLastTimeMessageArrived == false )
//            {
//                if( wParam == VK_ESCAPE && pFramework->m_EscapeButtonWillQuit )
//                    pFramework->m_CloseProgramRequested = true;
//
//                pFramework->m_KeyStates[wParam] = true;
//            }
//
//            Event* pEvent = new InputEvent(InputDeviceTypes::InputDeviceType_Keyboard, InputStates::InputState_Pressed, wParam, 0 );
//            pFramework->GetGameCore()->GetEventManager()->QueueEvent( pEvent );
//            return 0;
//        }
//        case WM_KEYUP:
//        {
//            pFramework->m_KeyStates[wParam] = false;
//
//            Event* pEvent = new InputEvent(InputDeviceTypes::InputDeviceType_Keyboard, InputStates::InputState_Released, wParam, 0 );
//            pFramework->GetGameCore()->GetEventManager()->QueueEvent( pEvent );
//            return 0;
//        }
//        case WM_MOUSEMOVE:
//        {
//            int x = GET_X_LPARAM( lParam );
//            int y = GET_Y_LPARAM( lParam );
//            return 0;
//        }
//        case WM_LBUTTONDOWN:
//        {
//            pFramework->m_MouseButtonStates[0] = true;
//
//            int x = GET_X_LPARAM( lParam );
//            int y = GET_Y_LPARAM( lParam );
//            return 0;
//        }
//        case WM_LBUTTONUP:
//        {
//            pFramework->m_MouseButtonStates[0] = false;
//
//            int x = GET_X_LPARAM( lParam );
//            int y = GET_Y_LPARAM( lParam );
//        return 0;
//        }
//        case WM_SIZE:
//        {
//            pFramework->ResizeWindow( LOWORD(lParam), HIWORD(lParam) );
//            return 0;
//        }
//        default:
//            break;
//    }
//
//    // Pass all unhandled messages to DefWindowProc
//    return DefWindowProc( hWnd, uMsg, wParam, lParam );
//}

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
