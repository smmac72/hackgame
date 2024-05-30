#pragma once

enum class EWindowStates
{
    WINDOW_MAINMENU,
    WINDOW_GAME,
    WINDOW_CALL,
    WINDOW_EXIT
};

class Window
{
public:
    Window();
    EWindowStates GetWindowState();
    void SetWindowState(EWindowStates newState);
private:
    EWindowStates WindowState;
};
