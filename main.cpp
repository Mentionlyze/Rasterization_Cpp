#include "Application.h"
#include "Renderer.h"
#include <iostream>

#define VIEWPORT_TITLE "Rasterization"
#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 900

int main() {
  auto vec = CGMath::Color{0.2f, 0.9f, 0.0f, 1.0f};

  auto app = new Rasterization::Application(VIEWPORT_TITLE, VIEWPORT_WIDTH,
                                            VIEWPORT_HEIGHT);
  auto renderer = Rasterization::CreateRef<Rasterization::Renderer>(
      VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
  app->Run([renderer]() {
    renderer->Clear({0.0f, 0.0f, 0.0f, 1.0f});
    renderer->ClearDepth(1.0);

    renderer->DrawLine({-100.0f, 0.0f}, {100.0f, 0.0f},
                       {0.2f, 0.9f, 0.0f, 1.0f});

    renderer->DrawLine({0.0f, -100.0f}, {0.0f, 100.0f},
                       {0.2f, 0.9f, 0.0f, 1.0f});

    renderer->DrawLine({-100.0f, 2000.0f}, {200.0f, 500.0f},
                       {0.2f, 0.9f, 0.0f, 1.0f});

    CGMath::Vec3 vertices[3] = {
        CGMath::Vec3{-1.0f, 1.0f, -2.0f},
        CGMath::Vec3{1.0f, 1.0f, -2.0f},
        CGMath::Vec3{0.0f, -1.0f, -2.0f},
    };

    // renderer->DrawTriangle(glm::mat4(1.0f), vertices, {0.2f, 0.9f,
    // 0.0f, 1.0f});

    auto v = CGMath::Vec3{1.9f, 1.7f, 1.1f};
    v * 2.0f;
    std::cout << v << "\n";

    auto m1 = CGMath::CreatePersp(CGMath::Deg2Rad(45.0f), 1280.0f / 900.0f,
                                  0.1f, 1000.f, 1);
    auto m2 = CGMath::Mat4::Identity();

    auto m3 = m1 * m2;

    std::cout << m3.data[0] << "\n";

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
