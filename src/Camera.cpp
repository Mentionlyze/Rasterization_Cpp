#include "Camera.h"

namespace Rasterization {
Camera::Camera(const float fov, const float aspect, const float near,
               const float far)
    : m_Frustum{CreateRef<Frustum>(fov, aspect, near, far)} {}
} // namespace Rasterization