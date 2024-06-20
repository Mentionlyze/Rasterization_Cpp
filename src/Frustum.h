#pragma once

#include "math/CGMath.h"
namespace Rasterization {
class Frustum {
public:
  Frustum(const float fov, const float aspect, const float near,
          const float far);
  ~Frustum() = default;

  CGMath::Mat4 &GetMat() { return m_Mat; }

private:
  float m_Fov, m_Aspect, m_Near, m_Far;
  CGMath::Mat4 m_Mat;
};
} // namespace Rasterization