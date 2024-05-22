#pragma once

#include <cstddef>
#include <ostream>
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

  constexpr Vec3(float x, float y, float z) : x{x}, y{y}, z{z} {}
  constexpr Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

  float operator[](size_t index) {
    float set[3] = {x, y, z};
    return set[index];
  }

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &vec3) {
    return out << "vec3(" << vec3.x << "," << vec3.y << "," << vec3.z << ")";
  }
};

struct Vec4 {
  union {
    struct {
      float x, y, z, w;
    };
    struct {
      float r, g, b, a;
    };
  };

  constexpr Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
  constexpr Vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

  float operator[](size_t index) {
    float set[4] = {x, y, z, w};
    return set[index];
  }

  friend std::ostream &operator<<(std::ostream &out, const Vec4 &vec4) {
    return out << "vec4(" << vec4.x << "," << vec4.y << "," << vec4.z << ","
               << vec4.w << ")";
  }
};

unsigned char Float2UChar(const float f);
float UChar2Float(const unsigned char c);
} // namespace Rasterization