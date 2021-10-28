#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include <GLFW/glfw3.h> // for types

#define WIDTH  600
#define HEIGHT 600

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

struct vertex_data {
  vec2 position;
  vec4 color;
};

class TriangleRenderer {
private:
  GLFWwindow * window; // The place we are rendering everything
  glid vao;            // vertex array object
  glid vertex_buffer;  // the vertex buffer object
  glid element_buffer; // buffer containing the index data

  glid shader_program; // the shader pipeline

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
  void afterSwap(); // things to do between iterations
};

#endif
