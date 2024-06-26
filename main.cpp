#include "Application.h"
#include "Renderer.h"
#include "core/math/Math.h"
#include <iostream>

#define VIEWPORT_TITLE "Rasterization"
#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 900

int main() {
  auto vec = Math::Color{0.2f, 0.9f, 0.0f, 1.0f};

  auto app = new Rasterization::Application(VIEWPORT_TITLE, VIEWPORT_WIDTH,
                                            VIEWPORT_HEIGHT);
  auto renderer =
      Rasterization::Renderer::Create(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

  float radians = Math::Deg2Rad(0);

  app->Run([&]() {
    renderer->Clear({0.0f, 0.0f, 0.0f, 1.0f});
    renderer->ClearDepth(1.0);

    // renderer->DrawLine({-100.0f, 0.0f}, {100.0f, 0.0f},
    //                    {0.2f, 0.9f, 0.0f, 1.0f});

    // renderer->DrawLine({0.0f, -100.0f}, {0.0f, 100.0f},
    //                    {0.2f, 0.9f, 0.0f, 1.0f});

    // renderer->DrawLine({-100.0f, 2000.0f}, {200.0f, 500.0f},
    //                    {0.2f, 0.9f, 0.0f, 1.0f});

    Math::Vec3 vertices[3] = {
        Math::Vec3{-1.0f, 1.0f, 0.0f},
        Math::Vec3{1.0f, 1.0f, 0.0f},
        Math::Vec3{0.0f, -1.0f, 0.0f},
    };

    auto trans = Math::CreateTranslation(
        static_cast<Math::Vec3>(Math::Vec4{0.0f, 0.0f, -4.0f, 1.0f}));

    auto model = trans * Math::CreateYRotation(radians);

    std::cout << model.data[0] << "\n";

    renderer->DrawTriangle(model, vertices, {0.2f, 0.9f, 0.0f, 1.0f});

    radians += 0.01f;

    auto v = Math::Vec3{1.9f, 1.7f, 1.1f};
    v * 2.0f;

    auto m1 = Math::CreatePersp(Math::Deg2Rad(30.0f), 1280.0f / 900.0f, 0.1f,
                                1000.f, 1);
    auto m2 = Math::Mat4::Identity();

    auto m3 = m1 * m2;

    auto v4 = m3 * Math::Vec4{-1.0f, 1.0f, -2.0f, 1.0f};

    // std::cout << v4.x << "\n";

    // renderer->DrawLine({0.0, 0.0}, {200, 300}, {0.2f, 0.9f, 0.0f, 1.0f});
    // renderer->DrawLine(0, 0, 300, 100, glm::vec4{0.2f, 0.9f,
    // 0.0f, 1.0f}); renderer->DrawLine(200, 300, 50, 120, glm::vec4{0.2f,
    // 0.8f, 0.0f, 1.0f}); renderer->GetFrameBuffer()->SetColor(20, 20,
    // {0.5f, 0.2f, 0.0f, 1.0f}); renderer->GetFrameBuffer()->SetColor(20,
    // 21, {0.5f, 0.2f, 0.0f, 1.0f});
    // renderer->GetFrameBuffer()->SetColor(21, 20, {0.5f, 0.2f,
    // 0.0f, 1.0f}); renderer->GetFrameBuffer()->SetColor(21, 21, {0.5f,
    // 0.2f, 0.0f, 1.0f});

    Rasterization::Application::SwapBuffers(renderer);
  });

  delete app;
}
