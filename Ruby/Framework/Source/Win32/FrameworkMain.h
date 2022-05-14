#pragma once

struct GLFWwindow;
class GameCore;

class Framework
{
public:
    Framework();

    void Init(int width, int height);
    void Run(GameCore* pGameCore);
    void Shutdown() const;
    void SetWindowSize(int width, int height);

    void GetMouseCoordinates(int* mx, int* my) const {}
    [[nodiscard]] unsigned int GetWindowWidth() const { return m_CurrentWindowWidth; }
    [[nodiscard]] unsigned int GetWindowHeight() const { return m_CurrentWindowHeight; }
    [[nodiscard]] GameCore* GetGameCore() const { return m_pGameCore; }

protected:
    void ResizeWindow(int width, int height);
    bool CreateGLWindow(const char* title, int width, int height, char colorbits, char zbits, char stencilbits, bool fullscreenflag);
    void KillGLWindow() const;
    static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
    static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
    static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
    static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

    GLFWwindow* myWindow;
    GameCore* m_pGameCore;
    int m_InitialWindowWidth;
    int m_InitialWindowHeight;
    int m_CurrentWindowWidth;
    int m_CurrentWindowHeight;
    bool m_FullscreenMode;
};