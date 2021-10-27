/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>

// for debugging!
#include <fstream> // for reading in a file
#include <string> // std::string
#include "glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>
// end debugging

#include "graphics/triangles.h"

int main() {
  printf("Hello, world\n");
  TriangleRenderer renderer; // calls constructor

  // render loop ends when window has the should close property set to true
  while(!renderer.shouldClose()) {
    renderer.processInput(); // process input first so that window reacts as soon as possible

    renderer.draw(); // draw to backbuffer

    renderer.swapBuffer(); // display the buffer we drew to
    renderer.afterSwap(); // does whatever needs to be done after the buffer is swapped
  }
  renderer.terminate();
  return 0;
}
