#include "WindowsWindow.h"
#include "Base.h"

#define RASTERIZATION_ENTRY_NAME "Entry"
#define RASTERIZATION_CLASS_NAME "Class"

namespace Rasterization {
WindowsWindow::WindowsWindow(const std::string &title, const uint32_t width,
                             const uint32_t height)
    : m_Title{title}, m_Width{width}, m_Height{height}, m_Closed{true},
      m_Inited{false} {
  Init();

  DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT rect;
  rect.left = 0;
  rect.top = 0;
  rect.bottom = (long)height;
  rect.right = (long)width;
  AdjustWindowRect(&rect, style, false);

  m_Handle = CreateWindow(RASTERIZATION_CLASS_NAME, m_Title.c_str(), style,
                          CW_USEDEFAULT, 0, rect.right - rect.left,
                          rect.bottom - rect.top, nullptr, nullptr,
                          GetModuleHandle(nullptr), nullptr);
  ASSERT(m_Handle != nullptr);
  m_Closed = false;

  SetProp(m_Handle, RASTERIZATION_ENTRY_NAME, this);

  HDC windowDC = GetDC(m_Handle);
  m_MemoryDC = CreateCompatibleDC(windowDC);

  BITMAPINFOHEADER biHeader = {};
  HBITMAP newBitmap;
  HBITMAP oldBitmap;

  biHeader.biSize = sizeof(BITMAPINFOHEADER);
  biHeader.biWidth = (long)width;
  biHeader.biHeight = -(long)height;
  biHeader.biPlanes = 1;
  biHeader.biBitCount = 24;
  biHeader.biCompression = BI_RGB;

  newBitmap = CreateDIBSection(m_MemoryDC, (BITMAPINFO *)&biHeader,
                               DIB_RGB_COLORS, (void **)&m_Buffer, nullptr, 0);
  ASSERT(newBitmap != nullptr);
  constexpr uint32_t channelCount = 3;
  uint32_t size = m_Width * m_Height * channelCount * sizeof(u_char);
  memset(m_Buffer, 0, size);
  oldBitmap = (HBITMAP)SelectObject(m_MemoryDC, newBitmap);

  DeleteObject(oldBitmap);
  ReleaseDC(m_Handle, windowDC);

  Show();
}

WindowsWindow::~WindowsWindow() {
  ShowWindow(m_Handle, SW_HIDE);
  RemoveProp(m_Handle, RASTERIZATION_ENTRY_NAME);
  DeleteDC(m_MemoryDC);
  DestroyWindow(m_Handle);
}

void WindowsWindow::Init() {
  ASSERT(!m_Inited);
  Register();
  m_Inited = true;
}

void WindowsWindow::Terminate() {
  ASSERT(m_Inited);
  UnRegister();
  m_Inited = false;
}

void WindowsWindow::Show() {
  HDC windowDC = GetDC(m_Handle);
  BitBlt(windowDC, 0, 0, m_Width, m_Height, m_MemoryDC, 0, 0, SRCCOPY);
  ShowWindow(m_Handle, SW_SHOW);
  ReleaseDC(m_Handle, windowDC);
}

void WindowsWindow::Register() {
  ATOM atom;
  WNDCLASS wc = {0};
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)(WHITE_BRUSH);
  wc.hCursor = nullptr;
  wc.hIcon = nullptr;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.lpfnWndProc = WindowsWindow::WndProc;
  wc.lpszClassName = RASTERIZATION_CLASS_NAME;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpszMenuName = nullptr;
  atom = RegisterClass(&wc);
}

void WindowsWindow::UnRegister() {
  UnregisterClass(RASTERIZATION_CLASS_NAME, GetModuleHandle(nullptr));
}

void WindowsWindow::DrawFrameBuffer(const Ref<FrameBuffer> frameBuffer) {
  auto f_Width = frameBuffer->GetWidth();
  auto f_Height = frameBuffer->GetHeight();

  for (uint32_t i = 0; i < f_Height; i++) {
    for (uint32_t j = 0; j < f_Width; j++) {
      constexpr uint32_t channelCount = 3;
      constexpr uint32_t rChannel = 2;
      constexpr uint32_t gChannel = 1;
      constexpr uint32_t bChannel = 0;

      auto color = frameBuffer->GetColor(j, f_Height - 1 - i);
      const uint32_t pixelStart = (i * f_Width + j) * channelCount;
      const uint32_t rIndex = pixelStart + rChannel;
      const uint32_t gIndex = pixelStart + gChannel;
      const uint32_t bIndex = pixelStart + bChannel;

      m_Buffer[rIndex] = color[0] * 255.0;
      m_Buffer[gIndex] = color.g;
      m_Buffer[bIndex] = color.b;
    }
  }

  Show();
};

void WindowsWindow::PollInputEvents() {
  MSG message;
  while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
};

LRESULT CALLBACK WindowsWindow::WndProc(const HWND hWnd, const UINT msgID,
                                        const WPARAM wParam,
                                        const LPARAM lParam) {
  auto window = (WindowsWindow *)GetProp(hWnd, RASTERIZATION_ENTRY_NAME);
  if (window == nullptr) {
    return DefWindowProc(hWnd, msgID, wParam, lParam);
  }

  switch (msgID) {
  case WM_DESTROY:
    window->m_Closed = true;
    return 0;
  }

  return DefWindowProc(hWnd, msgID, wParam, lParam);
}

} // namespace Rasterization