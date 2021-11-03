/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>
#include <math.h> // for sin
#include <fstream> // for reading in a file
#include <string> // std::string

#include "graphics/glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "shader.h" // for ShaderProgram

// Called every time window is resized
static void
framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}  

void
BoardRenderer::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    printf("Escape key pressed\n");
    glfwSetWindowShouldClose(window, true);
  }
}

void BoardRenderer::draw() {
  // clear buffer
  glClearColor(.2f, .3f, .3f, 1.f); // sets the color that we are clearing to a dark blue-green
  glClear(GL_COLOR_BUFFER_BIT); // clears backbuffer

  // assign color that's a function of time
  float t = glfwGetTime();
  float val = 0.5 + (0.5 * sin(t));
  shader_program->use(); // use the shader program
  // Set uniforms
  shader_program->setFloat("time_val", val);

  // draw triangles
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool BoardRenderer::shouldClose() {
  return glfwWindowShouldClose(window);
}

void BoardRenderer::afterSwap() {
  glfwPollEvents(); // looks for any new events
  frame_counter++;
}

// all rendering is done on backbuffer, this swaps with front buffer, flushing backbuffer
void BoardRenderer::swapBuffer() {
  glfwSwapBuffers(window);
}

void BoardRenderer::terminate() {
  glfwTerminate();
}

BoardRenderer::~BoardRenderer() {
  if (shader_program != nullptr)
    delete shader_program;
}

BoardRenderer::BoardRenderer() {
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

  // Compile shaders and link them together into an active program
  const GLenum shader_types[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
  const char * shader_paths[] = {"shaders/default.vert", "shaders/default.frag"};
  shader_program = new ShaderProgram(2, shader_types, shader_paths);

  // TODO: set a constant width for a square, get current size of screen to figure it out
  //      2. Make vertex_data have a boolean instead of a color
  //      3. Make 2 uniforms for different colors
  //      4. Generate triangles and indices for each square on the board sequentially.

  // DEFINE TRIANGLE
  // [-1, 1] x [-1, 1]
  vertex_data vertices[] = {
    {{-0.5f,  0.5f},{0. ,1. ,0. ,1. }},
    {{-0.5f, -0.5f},{1. ,0. ,0. ,1. }}, 
    {{ 0.5f, -0.5f},{0. ,0. ,1. ,1. }}, 
    {{ 0.5f,  0.5f},{0. ,0. ,0.5,1.}}
  };
  unsigned int indices[] = {
    0,1,2,
    0,2,3
  };
  // vertex buffer, for abstracting memory transfer between CPU and GPU

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

  // these functions apply to vertex_buffer above
  glGenBuffers(1, &vertex_buffer); // 1 is the number of buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // element buffer
  glGenBuffers(1, &element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer); // binds element_buffer for whatever the below call
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


  // args: which array, number of components in an array, type (size) of each attribute, whether to normalize, stride, offset of start of data
  // These lines set up the attributes of the vertex buffer object
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0); // specifies 1 attribute of each vertex: the position
	glEnableVertexArrayAttrib(vao, 0); // enables the first attribute of the vertex array
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)(2*sizeof(float))); // specifies 1 attribute of each vertex: the position
	glEnableVertexArrayAttrib(vao, 1); // enables the first attribute of the vertex array
}
