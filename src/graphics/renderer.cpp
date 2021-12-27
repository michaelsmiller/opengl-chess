/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>
#include <cmath> // for sin, lerp
#include <fstream> // for reading in a file
#include <string> // std::string

#include "graphics/glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "shader.h" // for ShaderProgram
/* #include "util/util.h" */

using std::lerp;

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

void
BoardRenderer::draw() {
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
  glDrawElements(GL_TRIANGLES, nsquares*6, GL_UNSIGNED_INT, 0);
}

bool
BoardRenderer::shouldClose() {
  return glfwWindowShouldClose(window);
}

void
BoardRenderer::afterSwap() {
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
  delete square_data;
  delete square_indices;
}

BoardRenderer::BoardRenderer() {
  frame_counter = 0;
  // configure GLFW window handling
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window (width, height, name)
  window = glfwCreateWindow(WIDTH, HEIGHT, "Josh is a fucking moron!", NULL, NULL);
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
  /* nsquares = 2; */
  /* square_data = new vertex_data[nsquares*4]; */
  /* square_indices  = new u32[nsquares*6]; */

  /* square_data[0] = {{ 0.0f,  0.9f},{0,0}}; */
  /* square_data[1] = {{ 0.0f,  0.0f},{0,0}}; */
  /* square_data[2] = {{ 0.9f,  0.0f},{0,0}}; */
  /* square_data[3] = {{ 0.9f,  0.9f},{0,0}}; */

  /* square_data[4] = {{-0.9f,  0.0f},{0,0}}; */
  /* square_data[5] = {{-0.9f, -0.9f},{0,0}}; */
  /* square_data[6] = {{ 0.0f, -0.9f},{0,0}}; */
  /* square_data[7] = {{ 0.0f,  0.0f},{0,0}}; */

  /* square_indices[0] = 0; */
  /* square_indices[1] = 1; */
  /* square_indices[2] = 2; */
  /* square_indices[3] = 0; */
  /* square_indices[4] = 2; */
  /* square_indices[5] = 3; */

  /* square_indices[6]  = 4; */
  /* square_indices[7]  = 5; */
  /* square_indices[8]  = 6; */
  /* square_indices[9]  = 4; */
  /* square_indices[10] = 6; */
  /* square_indices[11] = 7; */

  const int dim = 8;
  nsquares = dim*dim;
  const float nvertices_per_side = (float)(dim+1); // what is this
  square_data = new vertex_data[nsquares*4]; // 4 vertices per square
  square_indices = new u32[nsquares*3*2]; // 2 triangles with 3 vertices each;
  for (int i = 0, ij=0; i < dim; i++) {
    float y1 = lerp(-1.f, 1.f, i/nvertices_per_side);
    float y2 = lerp(-1.f, 1.f, (i+1)/nvertices_per_side);
    for (int j = 0; j < dim; j++, ij++) {
      float x1 = lerp(-1.f, 1.f, j/nvertices_per_side);
      float x2 = lerp(-1.f, 1.f, (j+1)/nvertices_per_side);
      square_data[4*ij+0] = {{x1, y2}, {i, j}};
      square_data[4*ij+1] = {{x1, y1}, {i, j}};
      square_data[4*ij+2] = {{x2, y1}, {i, j}};
      square_data[4*ij+3] = {{x2, y2}, {i, j}};

      const u32 base = 4*ij;
      square_indices[6*ij+0] = base+0;
      square_indices[6*ij+1] = base+1;
      square_indices[6*ij+2] = base+2;
      square_indices[6*ij+3] = base+0;
      square_indices[6*ij+4] = base+2;
      square_indices[6*ij+5] = base+3;
    }
  }


  // vertex buffer, for abstracting memory transfer between CPU and GPU
  printf("nsquares: %d\n", nsquares);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

  // these functions apply to vertex_buffer above
  glGenBuffers(1, &vertex_buffer); // 1 is the number of buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 4*nsquares*sizeof(vertex_data), square_data, GL_STATIC_DRAW);
	/* glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vertex_data), square_data, GL_STATIC_DRAW); */

  // element buffer
  glGenBuffers(1, &element_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer); // binds element_buffer for whatever the below call
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*nsquares*sizeof(u32), square_indices, GL_STATIC_DRAW);
  /* glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24*sizeof(u32), square_indices, GL_STATIC_DRAW); */


  // args: which array, number of components in an array, type (size) of each attribute, whether to normalize, stride, offset of start of data
  // These lines set up the attributes of the vertex buffer object
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_data), (void*)0); // specifies 1 attribute of each vertex: the position
	glEnableVertexArrayAttrib(vao, 0); // enables the first attribute of the vertex array
	glVertexAttribPointer(1, 2, GL_INT, GL_FALSE, sizeof(vertex_data), (void*)(sizeof(vec2))); // specifies 1 attribute of each vertex: the position
	glEnableVertexArrayAttrib(vao, 1); // enables the first attribute of the vertex array
}
