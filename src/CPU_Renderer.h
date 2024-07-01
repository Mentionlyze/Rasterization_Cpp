#pragma once

#include "Renderer.h"
namespace Rasterization {

class CPU_Renderer : public Renderer {
public:
  CPU_Renderer(const int32_t width, const int32_t height);
  ~CPU_Renderer() = default;

  const int32_t GetCanvasWith() const override { return m_Width; };
  const int32_t GetCanvasHeight() const override { return m_Height; }

  const Ref<FrameBuffer> GetFrameBuffer() const override {
    return m_FrameBuffer;
  }
  const Ref<Camera> GetCamera() const override { return m_Camera; };

  void Clear(const Math::Color &color) override { m_FrameBuffer->Clear(color); }

  void ClearDepth(const float depth) override {
    m_FrameBuffer->ClearDepth(depth);
  }

  void DrawTriangle(const Math::Mat4 &model, const Math::Vec3 (&vertices)[3],
                    const Math::Color &color) override;

  void DrawLine(const Math::Vec2 &point_1, const Math::Vec2 &point_2,
                const Math::Color &color) override;

private:
  void DrawLineWithoutClip(const Math::Vec2 &p1, const Math::Vec2 &p2,
                           const Math::Color &color);

  int32_t m_Width, m_Height;
  Ref<FrameBuffer> m_FrameBuffer;
  Ref<Camera> m_Camera;
  ViewPort m_ViewPort;
};
} // namespace Rasterization