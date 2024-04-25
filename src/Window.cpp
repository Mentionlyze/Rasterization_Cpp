#include "WindowsWindow.h"

namespace Rasterization {
std::unique_ptr<Window> Window::Create(const std::string &title,
                                       const uint32_t width,
                                       const uint32_t height) {
  return std::make_unique<WindowsWindow>(title, width, height);
}
} // namespace Rasterization