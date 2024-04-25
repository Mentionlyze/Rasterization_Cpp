#include "WindowsWindow.h"
#include "Base.h"

namespace Rasterization {
WindowsWindow::WindowsWindow(const std::string &title, const uint32_t width,
                             const uint32_t height)
    : m_Title(title), m_Width(width), m_Height(height), m_Inited(false) {}

WindowsWindow::~WindowsWindow() {}

void WindowsWindow::Init() {
  ASSERT(!m_Inited);
  Register();
  m_Inited = true;
}

void WindowsWindow::Terminate() {
  ASSERT(m_Inited);
  UnRegister();
  m_Inited = false;
}

void WindowsWindow::Show() {}

void WindowsWindow::Register() {}

void WindowsWindow::UnRegister() {}
} // namespace Rasterization