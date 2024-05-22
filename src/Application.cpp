#include "Application.h"

namespace Rasterization {

Application::Application(const std::string &title, const uint32_t width,
                         const uint32_t height)
    : m_Title(title), m_Width(width), m_Height(height) {
  Init();
}

Application::~Application() { Terminate(); }

void Application::Init() {
  m_Window = Window::Create(m_Title, m_Width, m_Height);
}

void Application::Run() {

  while (!m_Window->Closed()) {
    OnUpdate();

    m_Window->PollInputEvents();
  }
}

void Application::Terminate() { m_Window->Terminate(); }

void Application::OnUpdate() {
  auto frameBuffer = CreateRef<FrameBuffer>(m_Width, m_Height);
  frameBuffer->Clear({0.5f, 0.3f, 0.5f});
  frameBuffer->ClearDepth();
  m_Window->DrawFrameBuffer(frameBuffer);
}

} // namespace Rasterization