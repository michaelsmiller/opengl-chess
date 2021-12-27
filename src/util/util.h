#ifndef UTIL_H_
#define UTIL_H_

#include <stdlib.h>
#include <stdio.h>

// TODO: add another macro to deal with shutting down OpenGL

#define ERROR(...) \
{ \
  fprintf(stderr, __VA_ARGS__); \
  fprintf(stderr, "\n"); \
  exit(1); \
}


#endif
