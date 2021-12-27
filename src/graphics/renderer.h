#ifndef TRIANGLES_H_
#define TRIANGLES_H_

#include <GLFW/glfw3.h> // for types

#include <util/types.h> // for glid, vec2, vec4

#define WIDTH  600
#define HEIGHT 600

class ShaderProgram; // forward definition, in shader.h

struct vertex_data {
  vec2 position;
  ivec2 index;
};

class BoardRenderer {
private:
  // The OpenGL stuff
  GLFWwindow * window; // The place we are rendering everything
  glid vao;            // vertex array object
  glid vertex_buffer;  // the vertex buffer object
  glid element_buffer; // buffer containing the index data
  ShaderProgram * shader_program; // the shader pipeline
  int frame_counter;

  // The actual vertices and images
  int nsquares;
  vertex_data * square_data;
  u32 * square_indices;


public:
  // Instantiate window
  BoardRenderer();
  ~BoardRenderer();

  void addRenderer(const char * name, const GLenum shader_type);
  bool shouldClose();
  void processInput();
  void draw();
  void swapBuffer();

  void terminate();
  void afterSwap(); // things to do between iterations
};

#endif
