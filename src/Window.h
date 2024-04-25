#include <cstdint>
#include <memory>
#include <string>
namespace Rasterization {
class Window {
public:
  virtual ~Window() = default;

  virtual void Init() = 0;

  virtual void Terminate() = 0;

  virtual void Show() = 0;

  virtual bool Closed() const = 0;

public:
  static std::unique_ptr<Window>
  Create(const std::string &title, const uint32_t width, const uint32_t height);
};
} // namespace Rasterization