#include "Math.h"

namespace Rasterizition {

unsigned char Float2UChar(const float f) { return (unsigned char)(f * 255.0f); }
float UChar2Float(const unsigned char c) { return (float)c / 255.0f; }

} // namespace Rasterizition