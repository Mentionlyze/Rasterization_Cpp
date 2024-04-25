#pragma once
#include <cstdint>
#include <string>

namespace Rasterization {
class Application {
public:
  Application(const std::string &name, const uint32_t widht,
              const uint32_t height);
  ~Application();

  void Run();

private:
  void Init();
  void Terminate();
  void OnUpdate();

private:
  std::string m_Name;
  uint32_t m_Width, m_Height;
};
} // namespace Rasterization