/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>

#include <fstream> // for reading in a file
#include <string> // std::string

#include "glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

// Called every time window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}  

unsigned int compileShader(const char * filename, GLenum shader_type) {
  /* std::ifstream file(filename); */
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

unsigned int createVertexBuffer(GLFWwindow * window) {
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  }; 

  // vertex buffer, for abstracting memory transfer between CPU and GPU
  unsigned int VBO;
  glGenBuffers(1, &VBO); // 1 is the number of buffers
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // can use GL_DYNAMIC_DRAW to specify that the data will change.

  // args: location of vertex attribute, size of each attribute, whether to normalize, stride, offset of start of data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  return VBO;
}


GLFWwindow * initGLFW() {
  glfwInit();
  // configure GLFW window handling
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window (width, height, name)
  GLFWwindow* window = glfwCreateWindow(800, 600, "I am a god", NULL, NULL);
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

  // Set viewport (this is openGL, not GLFW)
  glViewport(0, 0, 800, 600); // this is wrt the window
  // Can make other viewports for other things we want to display

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // sets the function to be called
  unsigned int VBO = createVertexBuffer(window);
  unsigned int vertex_shader = compileShader("shaders/default.vert", GL_VERTEX_SHADER);
  unsigned int fragment_shader = compileShader("shaders/default.frag", GL_FRAGMENT_SHADER);

  // link shaders into a shader program, representing a user controlled part of the graphics pipeline
  unsigned int shader_program = glCreateProgram();
  // order matters
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

  // actually draw triangle


  return window;
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    printf("Escape key pressed\n");
    glfwSetWindowShouldClose(window, true);
  }
}

int main() {
  GLFWwindow* window = initGLFW();
  printf("Hello, world\n");

  // render loop ends when window has the should close property set to true
  while(!glfwWindowShouldClose(window)) {
    processInput(window); // process input first so that window reacts as soon as possible

    // rendering commands go here
    glClearColor(.2f, .3f, .3f, 1.f); // sets the color that we are clearing to a dark blue-green
    glClear(GL_COLOR_BUFFER_BIT); // clears backbuffer

    glfwSwapBuffers(window); // all rendering is done on backbuffer, this swaps with front buffer, flushing backbuffer
    glfwPollEvents(); // looks for any new events
  }
  glfwTerminate();
  return 0;
}
