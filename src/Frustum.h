#pragma once

#include "math/Math.h"
namespace Rasterization {
class Frustum {
public:
  Frustum(const float fov, const float aspect, const float near,
          const float far);
  ~Frustum() = default;

  Math::Mat4 &GetMat() { return m_Mat; }

private:
  float m_Fov, m_Aspect, m_Near, m_Far;
  Math::Mat4 m_Mat;
};
} // namespace Rasterization