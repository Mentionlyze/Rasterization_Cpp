#pragma once

#include "Base.h"
#include "glm/glm.hpp"
namespace Rasterization {
class Frustum {
public:
  Frustum(const float fov, const float aspect, const float near,
          const float far);
  ~Frustum() = default;

  Ref<glm::mat4> GetMat() { return m_Mat; }

private:
  float m_Fov, m_Aspect, m_Near, m_Far;
  Ref<glm::mat4> m_Mat;
};
} // namespace Rasterization