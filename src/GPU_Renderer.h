#pragma once
#include "Renderer.h"

namespace Rasterization {

class GPU_Renderer : public Renderer {
public:
  GPU_Renderer(const int32_t width, const int32_t height);
  ~GPU_Renderer() = default;
};
} // namespace Rasterization
