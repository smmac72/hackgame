#include "../public/Window.h"

Window::Window()
{
    
}

EWindowStates Window::GetWindowState()
{
    return WindowState;
}

void Window::SetWindowState(EWindowStates newState)
{
    this->WindowState = newState;
}
