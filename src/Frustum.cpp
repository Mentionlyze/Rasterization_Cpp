#include "Frustum.h"
#include <cmath>

namespace Rasterization {

Frustum::Frustum(const float fov, const float aspect, const float near,
                 const float far)
    : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far} {

  float a = 1.0f / (near * tan(fov));

  // clang-format off
  m_Mat = glm::mat4(
    a,        0.0f,       0.0f,        0.0f,
    0.0f,     aspect * a, 0.0f,        0.0f,
    0.0f,     0.0f,       1.0f,        0.0f,
    0.0f,     0.0f,      -1.0f / near, 0.0f
  );
  // m_Mat = glm::perspective(fov, aspect,  near,  far);
}
} // namespace Rasterization