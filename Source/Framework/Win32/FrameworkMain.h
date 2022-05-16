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
    void SetWindowIcon(unsigned char* aSource, int aWidth, int aHeight) const;

    [[nodiscard]] unsigned int GetWindowWidth() const { return myCurrentWindowWidth; }
    [[nodiscard]] unsigned int GetWindowHeight() const { return myCurrentWindowHeight; }
    [[nodiscard]] GameCore* GetGameCore() const { return myGameCore; }

protected:
    void ResizeWindow(int width, int height);
    bool CreateGLWindow(const char* title, int width, int height);
    void KillGLWindow() const;
    static void KeyCallback(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
    static void CursorCallback(GLFWwindow* aWindow, double aXPosition, double aYPosition);
    static void ScrollCallback(GLFWwindow* aWindow, double aXOffset, double aYOffset);
    static void MouseButtonCallback(GLFWwindow* aWindow, int aButton, int anAction, int aModifiers);

    GLFWwindow* myWindow;
    GameCore* myGameCore;
    int myInitialWindowWidth;
    int myInitialWindowHeight;
    int myCurrentWindowWidth;
    int myCurrentWindowHeight;
};