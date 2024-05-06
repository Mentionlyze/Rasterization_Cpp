#pragma once
#include "Window.h"
#include <cstdint>
#include <string>

namespace Rasterization {
class Application {
public:
  Application(const std::string &title, const uint32_t width,
              const uint32_t height);
  ~Application();

  void Run();

private:
  void Init();
  void Terminate();
  void OnUpdate();

private:
  std::string m_Title;
  uint32_t m_Width, m_Height;

  Scope<Window> m_Window;
};
} // namespace Rasterization