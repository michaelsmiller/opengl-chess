#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>

// import math types too!
typedef GLuint glid; // for OpenGL objects

struct vec2 {
  float x;
  float y;
};
struct vec3 {
  float x;
  float y;
  float z;
};
struct vec4 {
  float x;
  float y;
  float z;
  float w;
};

typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t  i64;
typedef int32_t  i32;
typedef double   s64;
typedef float    s32;

typedef u32   b32;

#endif
