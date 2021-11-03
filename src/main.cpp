/* #include <GLFW/glfw3.h> */
#include <stdlib.h>
#include <stdio.h>

#include "graphics/renderer.h"

int main() {
  printf("Hello, world\n");
  BoardRenderer renderer; // calls constructor

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
