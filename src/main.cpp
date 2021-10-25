/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>

#include "glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

// Called every time window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
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
