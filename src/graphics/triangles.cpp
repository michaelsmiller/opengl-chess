/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>

#include <fstream> // for reading in a file
#include <string> // std::string

#include "glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

#include "triangles.h"

// Called every time window is resized
static void
framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}  

static glid
compileShader(const char * filename, GLenum shader_type) {
  std::ifstream file(filename, std::ifstream::binary);
  if (!file.is_open()) {
    printf("Could not open %s\n", filename);
    exit(1);
  }

  // get size of file
  file.seekg(0, file.end);
  int length = file.tellg();
  file.seekg(0, file.beg);

  char * buffer = new char[length];
  file.read(buffer, length);
  file.close();

  // shader shit with buffer
  unsigned int shader = glCreateShader(shader_type); // hardcode type of shader for now
  glShaderSource(shader, 1, &buffer, NULL);
  glCompileShader(shader);

  // check if compilation successful
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    printf("Failed to compile shader %s\n", filename);
    exit(1);
  }
  else {
    printf("Compiling shader: %s\n", filename);
  }

  delete[] buffer;
  return shader;
}

void
TriangleRenderer::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    printf("Escape key pressed\n");
    glfwSetWindowShouldClose(window, true);
  }
}

void TriangleRenderer::draw() {
  // clear buffer
  glClearColor(.2f, .3f, .3f, 1.f); // sets the color that we are clearing to a dark blue-green
  glClear(GL_COLOR_BUFFER_BIT); // clears backbuffer

  // draw triangles
  glDrawArrays(GL_TRIANGLES, 0, 3);
}


bool TriangleRenderer::shouldClose() {
  return glfwWindowShouldClose(window);
}

void TriangleRenderer::afterSwap() {
  glfwPollEvents(); // looks for any new events
  frame_counter++;
}

// all rendering is done on backbuffer, this swaps with front buffer, flushing backbuffer
void TriangleRenderer::swapBuffer() {
  glfwSwapBuffers(window);
}

void TriangleRenderer::terminate() {
  glfwTerminate();
}

TriangleRenderer::TriangleRenderer() {
  frame_counter = 0;
  // configure GLFW window handling
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window (width, height, name)
  window = glfwCreateWindow(WIDTH, HEIGHT, "Hello Triangle!", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create window\n");
    glfwTerminate();
    exit(-1);
  }
  glfwMakeContextCurrent(window);

  // initialize GLAD, should figure out OS and everything
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("GLAD failed :(\n");
    exit(1);
  }

  glViewport(0, 0, WIDTH, HEIGHT); // this is wrt the window
  // Can make other viewports for other things we want to display
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // sets the function to be called

  // SHADERS
  glid vertex_shader = compileShader("shaders/default.vert", GL_VERTEX_SHADER);
  glid fragment_shader = compileShader("shaders/default.frag", GL_FRAGMENT_SHADER);
  glid shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program); // I think this actually calls a linker, this is where dimensionality check happens
  int success;
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    printf("Failed to link shading program!\n");
    exit(1);
  }
  glUseProgram(shader_program);
  glDeleteShader(vertex_shader); // have to delete the objects once they are linked
  glDeleteShader(fragment_shader);


  // DEFINE TRIANGLE
  // [-1, 1] x [-1, 1]
  vec3 vertices[] = {
    {-0.5f, -0.5f, 0.0f},
    { 0.5f, -0.5f, 0.0f},
    { 0.0f,  0.5f, 0.0f}
  };
  // vertex buffer, for abstracting memory transfer between CPU and GPU

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

  glGenBuffers(1, &vertex_buffer); // 1 is the number of buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  // these functions apply to vertex_buffer above
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // args: which array, number of components in an array, type (size) of each attribute, whether to normalize, stride, offset of start of data
  // These lines set up the first attribute of the VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // specifies 1 attribute of each vertex: the position
	glEnableVertexArrayAttrib(vao, 0); // enables the first attribute of the vertex array
}
