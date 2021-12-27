#ifndef TYPES_H_
#define TYPES_H_

#include <stddef.h>
#include <GLFW/glfw3.h> // for GLuint

typedef GLuint glid; // for OpenGL objects

typedef uint64_t u64;
typedef uint32_t u32;
typedef int64_t  i64;
typedef int32_t  i32;
typedef double   s64;
typedef float    s32;
typedef u32   b32;

// math types
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

// this follows OpenGL
struct uvec2 {
  u32 x;
  u32 y;
};
// this follows OpenGL
struct ivec2 {
  int x;
  int y;
};


#endif
