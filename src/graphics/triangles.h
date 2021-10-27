#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include <GLFW/glfw3.h> // for types

#define WIDTH  600
#define HEIGHT 600

typedef GLuint glid; // for OpenGL objects

struct vec2 {
  union {
    struct {
      float x;
      float y;
    };
    float data[2];
  };
};
struct vec3 {
  union {
    struct {
      float x;
      float y;
      float z;
    };
    float data[3];
  };
};

class TriangleRenderer {
private:
  GLFWwindow * window; // The place we are rendering everything
  glid vao; // vertex array object
  glid vertex_buffer; // the vertex buffer object

  int frame_counter;

public:
  // Instantiate window
  TriangleRenderer();

  void addRenderer(const char * name, const GLenum shader_type);
  bool shouldClose();
  void processInput();
  void draw();
  void swapBuffer();

  void terminate();
  void afterSwap();
};

#endif
