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
    renderer->Clear({0.5f, 0.7f, 0.5f, 1.0f});
    renderer->ClearDepth();
    Rasterization::Application::SwapBuffers(renderer);
  });
  delete app;
}