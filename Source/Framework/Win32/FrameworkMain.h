#pragma once

struct GLFWwindow;
class GameCore;

class Framework
{
public:
    Framework();

    void Init(int aWidth, int aHeight);
    void Run(GameCore* aGameCore);
    void Shutdown() const;
    void SetWindowSize(int aWidth, int aHeight);
    void SetWindowIcon(unsigned char* aSource, int aWidth, int aHeight) const;

    [[nodiscard]] unsigned int GetWindowWidth() const { return myCurrentWindowWidth; }
    [[nodiscard]] unsigned int GetWindowHeight() const { return myCurrentWindowHeight; }
    [[nodiscard]] GameCore* GetGameCore() const { return myGameCore; }

private:
    void PrintDebugInfo() const;
    void ResizeWindow(int aWidth, int aHeight);
    bool CreateWindow(const char* aTitle, int aWidth, int aHeight);
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