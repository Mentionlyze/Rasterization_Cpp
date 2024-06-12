#pragma once
#include "Base.h"
#include "Renderer.h"
#include "Window.h"
#include <cstdint>
#include <string>

namespace Rasterization {
class Application {
public:
  Application(const std::string &title, const uint32_t width,
              const uint32_t height);
  ~Application();

  template <class _Update> void Run(_Update Func) {
    while (!m_Window->Closed()) {
      Func();
      m_Window->PollInputEvents();
    }
  };

  inline static Application &Get() { return *s_Instance; }

  inline static void SwapBuffers(Ref<Renderer> renderer) {
    auto test = renderer.get()->GetFrameBuffer()->GetColor(300, 500);
    Application::Get().m_Window->DrawFrameBuffer(renderer->GetFrameBuffer());
  }

private:
  void Init();
  void Terminate();
  void OnUpdate();

private:
  std::string m_Title;
  uint32_t m_Width, m_Height;

  Scope<Window> m_Window;
  static Application *s_Instance;
};
} // namespace Rasterization