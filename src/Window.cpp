#include "WindowsWindow.h"

namespace Rasterization {
Scope<Window> Window::Create(const std::string &title, const uint32_t width,
                             const uint32_t height) {

#ifdef USE_WINDOWS_WINDOW
  return CreateScope<WindowsWindow>(title, width, height);
#endif
}
} // namespace Rasterization