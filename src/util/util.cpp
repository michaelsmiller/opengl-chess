#include "util.h"

float lerp(const float a, const float b, const float t) {
  /* return (1-t)*a + t*b; */
  return a + t*(b-a); // monotonic and fast
}
