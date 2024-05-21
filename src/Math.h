#include <cstdint>
namespace Rasterization {
struct Vec3 {
  union {
    struct {
      float x, y, z;
    };
    struct {
      float r, g, b;
    };
  };
  constexpr Vec3() : x{0.0}, y{0.0}, z{0.0} {};
  constexpr Vec3(const float x, const float y, const float z)
      : x{x}, y{x}, z{y} {};

  float operator[](const uint32_t index) {
    float entry[] = {x, y, z};
    return entry[index];
  }
};

unsigned char Float2UChar(const float f);
float UChar2Float(const unsigned char c);
} // namespace Rasterization