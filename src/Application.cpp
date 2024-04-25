#include "Application.h"

namespace Rasterization {

Application::Application(const std::string &name, const uint32_t width,
                         const uint32_t height)
    : m_Name(name), m_Width(width), m_Height(height) {
  Init();
}

Application::~Application() {}

void Application::Init() {}

void Application::Run() {
  bool isRunning = true;
  while (isRunning) {
    OnUpdate();
  }
}

void Application::Terminate() {}

void Application::OnUpdate() {}

} // namespace Rasterization