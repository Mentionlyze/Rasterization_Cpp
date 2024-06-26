#pragma once

#include "Frustum.h"
#include "base/Base.h"

namespace Rasterization {
class Camera {
public:
  Camera(const float fov, const float aspect, const float near,
         const float far);
  ~Camera() = default;

  const Ref<Frustum> GetFrustum() const { return m_Frustum; }

private:
  Ref<Frustum> m_Frustum;
};
} // namespace Rasterization