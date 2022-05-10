#pragma once

class GameCore;

class Framework
{
public:
    Framework();

    void Init(int width, int height);
    int Run(GameCore* pGameCore);
    void Shutdown();
    void SetWindowSize(int width, int height);

    [[nodiscard]] bool IsKeyDown(int value) const;
    [[nodiscard]] bool IsMouseButtonDown(int id) const;

    void GetMouseCoordinates(int* mx, int* my) const;
    [[nodiscard]] unsigned int GetWindowWidth() const { return m_CurrentWindowWidth; }
    [[nodiscard]] unsigned int GetWindowHeight() const { return m_CurrentWindowHeight; }
    [[nodiscard]] GameCore* GetGameCore() const { return m_pGameCore; }

protected:
    void ResizeWindow(int width, int height);
    bool CreateGLWindow(const char* title, int width, int height, char colorbits, char zbits, char stencilbits, bool fullscreenflag);
    void KillGLWindow();
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    bool m_KeyStates[256];
    bool m_MouseButtonStates[3];
    HWND m_hWnd;
    HGLRC m_hRenderingContext;
    HDC m_hDeviceContext;
    HINSTANCE m_hInstance;
    GameCore* m_pGameCore;
    int m_InitialWindowWidth;
    int m_InitialWindowHeight;
    int m_CurrentWindowWidth;
    int m_CurrentWindowHeight;
    bool m_EscapeButtonWillQuit;
    bool m_CloseProgramRequested;
    bool m_WindowIsActive;
    bool m_FullscreenMode;
};