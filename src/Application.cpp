#include "Application.h"
#include "FrameBuffer.h"

namespace Rasterization {

Application *Application::s_Instance = nullptr;

Application::Application(const std::string &title, const uint32_t width,
                         const uint32_t height)
    : m_Title{title}, m_Width{width}, m_Height{height} {
  ASSERT(!s_Instance);
  s_Instance = this;
  Init();
}

Application::~Application() { Terminate(); }

void Application::Init() {
  m_Window = Window::Create(m_Title, m_Width, m_Height);
}

void Application::Terminate() { m_Window->Terminate(); }

void Application::OnUpdate() {
  auto frameBuffer = CreateRef<FrameBuffer>(m_Width, m_Height);
  frameBuffer->Clear({0.5f, 0.7f, 0.5f, 1.0f});
  frameBuffer->ClearDepth();
  m_Window->DrawFrameBuffer(frameBuffer);
}

} // namespace Rasterization