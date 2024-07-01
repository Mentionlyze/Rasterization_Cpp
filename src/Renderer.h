#pragma once

#include "Camera.h"
#include "FrameBuffer.h"
namespace Rasterization {

struct ViewPort {
  int32_t x, y, w, h;
};

class Renderer {
public:
  virtual ~Renderer() = default;

  virtual const int32_t GetCanvasWith() const = 0;
  virtual const int32_t GetCanvasHeight() const = 0;

  virtual const Ref<FrameBuffer> GetFrameBuffer() const = 0;

  virtual const Ref<Camera> GetCamera() const = 0;

  virtual void Clear(const Math::Color &color) = 0;

  virtual void ClearDepth(const float depth) = 0;

  virtual void DrawTriangle(const Math::Mat4 &model,
                            const Math::Vec3 (&vertices)[3],
                            const Math::Color &color) = 0;

  virtual void DrawLine(const Math::Vec2 &point_1, const Math::Vec2 &point_2,
                        const Math::Color &color) = 0;

  static Ref<Renderer> Create(const int32_t width, const int32_t height);
};
} // namespace Rasterization