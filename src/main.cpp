#include "Application.h"
#include "Renderer.h"

#define VIEWPORT_TITLE "Rasterization"
#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 900

int main() {
  auto app = new Rasterization::Application(VIEWPORT_TITLE, VIEWPORT_WIDTH,
                                            VIEWPORT_HEIGHT);
  auto renderer = Rasterization::CreateRef<Rasterization::Renderer>(
      VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
  app->Run([renderer]() {
    renderer->Clear({0.0f, 0.0f, 0.0f, 1.0f});
    renderer->ClearDepth(1.0);

    renderer->DrawLine(0, 0, 100, 300, {0.2f, 0.9f, 0.0f, 1.0f});
    renderer->DrawLine(0, 0, 300, 100, {0.2f, 0.9f, 0.0f, 1.0f});
    renderer->DrawLine(200, 300, 50, 120, {0.2f, 0.8f, 0.0f, 1.0f});
    // renderer->GetFrameBuffer()->SetColor(20, 20, {0.5f, 0.2f, 0.0f, 1.0f});
    // renderer->GetFrameBuffer()->SetColor(20, 21, {0.5f, 0.2f, 0.0f, 1.0f});
    // renderer->GetFrameBuffer()->SetColor(21, 20, {0.5f, 0.2f, 0.0f, 1.0f});
    // renderer->GetFrameBuffer()->SetColor(21, 21, {0.5f, 0.2f, 0.0f, 1.0f});

    Rasterization::Application::SwapBuffers(renderer);
  });
  delete app;
}