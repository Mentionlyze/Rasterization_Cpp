#pragma once

#include <cstddef>
#include <ostream>
namespace Rasterization {
struct Vec3 {
  union {
    struct {
      float X, Y, Z;
    };
    struct {
      float R, G, B;
    };
  };

  constexpr Vec3(float x, float y, float z) : X{x}, Y{y}, Z{z} {}
  constexpr Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}

  float operator[](size_t index) {
    float set[3] = {X, Y, Z};
    return set[index];
  }

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &vec3) {
    return out << "vec3(" << vec3.X << "," << vec3.Y << "," << vec3.Z << ")";
  }
};

unsigned char Float2UChar(const float f);
float UChar2Float(const unsigned char c);
} // namespace Rasterization