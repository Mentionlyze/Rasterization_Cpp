#include "Frustum.h"

namespace Rasterization {

Frustum::Frustum(const float fov, const float aspect, const float near,
                 const float far)
    : m_Fov{fov}, m_Aspect{aspect}, m_Near{near}, m_Far{far} {

  // clang-format off
  m_Mat = Math::CreateFrustum(fov, aspect, near, far, 1);
  // m_Mat = glm::perspective(fov, aspect,  near,  far);
}
} // namespace Rasterization