#include "Application.h"
#include "Renderer.h"
#include "glm/ext/vector_float4.hpp"
#include "thirdparty/glm/glm/fwd.hpp"

#define VIEWPORT_TITLE "Rasterization"
#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 900

int main() {
  auto vec = glm::vec4{0.2f, 0.9f, 0.0f, 1.0f};

  auto app = new Rasterization::Application(VIEWPORT_TITLE, VIEWPORT_WIDTH,
                                            VIEWPORT_HEIGHT);
  auto renderer = Rasterization::CreateRef<Rasterization::Renderer>(
      VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
  app->Run([renderer]() {
    renderer->Clear({0.0f, 0.0f, 0.0f, 1.0f});
    renderer->ClearDepth(1.0);

    renderer->DrawLine(glm::vec2{0.0f, 0.0f}, glm::vec2{200.0f, 200.0f},
                       {0.2f, 0.9f, 0.0f, 1.0f});

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