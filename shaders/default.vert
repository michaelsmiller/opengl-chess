#version 440 core
layout (location = 0) in vec2 position;
layout (location = 1) in ivec2 ind;

layout (location = 0) out vec4 vertexColor;

// uniform vec4 square_color1;

void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0); // directly given to OpenGL, the normalized coordinates of the fucker

    vec4 white = vec4(1., 1., 1., 1.); // white
    vec4 black = vec4(0., 0., 0., 1.); // black
    if (mod(int(ind.x) + int(ind.y), 2) == 0) {
    // if (int(ind.x) > 1<<30) {
      vertexColor = black;
      // vertexColor = black;
    }
    else {
      vertexColor = white;
    }
    // vertexColor = vec4(0.5, 0.5, 0.5, 1.);
    // vertexColor = aColor;
}
