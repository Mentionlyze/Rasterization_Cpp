#pragma once

#include <cmath>
#include <cstddef>
#include <iostream>

namespace Math {

template <typename T = float> struct Vec2 {
  union {
    struct {
      T x, y;
    };
    struct {
      T r, g;
    };
  };

private:
  T m_Data[2];

public:
  constexpr Vec2(T x, T y, T z) : x{x}, y{y}, m_Data{x, y} {}
  constexpr Vec2(T x) : x{x}, y{x}, m_Data{x, y} {}
  constexpr Vec2() : x{0.0f}, y{0.0f}, m_Data{x, y} {}

  T operator[](size_t index) { return m_Data[index]; }

  friend std::ostream &operator<<(std::ostream &out, const Vec2 &v) {
    return out << "vec2(" << v.x << "," << v.y << ")";
  }
};

struct Vec3 {
  union {
    struct {
      float x, y, z;
    };
    struct {
      float r, g, b;
    };
  };

private:
  float m_Data[3];

public:
  constexpr Vec3(float x, float y, float z)
      : x{x}, y{y}, z{z}, m_Data{x, y, z} {}
  constexpr Vec3(float x) : x{x}, y{x}, z{x}, m_Data{x, y, z} {}
  constexpr Vec3() : x{0.0f}, y{0.0f}, z{0.0f}, m_Data{x, y, z} {}
  constexpr Vec3(const Vec2<> &v) : x{v.x}, y{v.y}, z{0.0f}, m_Data{x, y, z} {}

  float operator[](size_t index) { return m_Data[index]; }

  friend std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
    return out << "vec3(" << v.x << "," << v.y << "," << v.z << ")";
  }

  float magnitude() const { return sqrt(x * x + y * y + z * z); }

  float dot(const Vec3 &v) const { return x * v.x + y * v.y + z * v.z; }

  Vec3 cross(const Vec3 &v) const {
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }

  Vec3 operator+(const Vec3 &v) { return Vec3{x + v.x, y + v.y, z + v.z}; }
  Vec3 &operator+=(const Vec3 &v) {
    *this = *this + v;
    return *this;
  }

  Vec3 operator-(const Vec3 &v) { return Vec3{x - v.x, y - v.y, z - v.z}; }
  Vec3 &operator-=(const Vec3 &v) {
    *this = *this - v;
    return *this;
  }

  Vec3 operator*(float n) { return Vec3{x * n, y * n, z * n}; }
  Vec3 &operator*=(float n) {
    *this = *this * n;
    return *this;
  }

  Vec3 operator/(float n) { return Vec3{x / n, y / n, z / n}; }
  Vec3 &operator/=(float n) {
    *this = *this / n;
    return *this;
  }

  void normalize() { *this /= magnitude(); }
  Vec3 normalized() { return *this / magnitude(); }
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

private:
  float m_Data[4];

public:
  constexpr Vec4(float x, float y, float z, float w)
      : x{x}, y{y}, z{z}, w{w}, m_Data{x, y, z, w} {}
  constexpr Vec4(float x) : x{x}, y{x}, z{x}, w{1.0f}, m_Data{x, y, z, w} {}
  constexpr Vec4(const Vec3 &vec3)
      : x{vec3.x}, y{vec3.y}, z{vec3.z}, w{1.0f}, m_Data{x, y, z, w} {}
  constexpr Vec4() : x{0.0f}, y{0.0f}, z{0.0f}, w{1.0f}, m_Data{x, y, z, w} {}

  float operator[](size_t index) { return m_Data[index]; }

  friend std::ostream &operator<<(std::ostream &out, const Vec4 &vec4) {
    return out << "vec4(" << vec4.x << "," << vec4.y << "," << vec4.z << ","
               << vec4.w << ")";
  }
};

struct Mat4 {
private:
  float m_Data[16];

public:
  // clang-format off
  constexpr Mat4(float a, float b, float c, float d, float e, float f, float g,
                 float h, float i, float j, float k, float l, float m, float n,
                 float o, float p)
      : m_Data{
             a, e, i, m,
             b, f, j, n,
             c, g,k,o,
            d,h,l,p,
        } {};
  constexpr Mat4()
      : m_Data{ 1.0f,  0.0f,  0.0f,  0.0f, 
               0.0f,  1.0f,  0.0f,  0.0f,
               0.0f,  0.0f, 1.0f, 0.0f, 
              0.0f, 0.0f, 0.0f, 1.0f} {}
  // clang-format on

  float operator[](size_t index) { return m_Data[index]; }
  // clang-format on
};

unsigned char Float2UChar(const float f);
float UChar2Float(const unsigned char c);
} // namespace Math