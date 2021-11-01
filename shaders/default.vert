#version 330 core
layout (location = 0) in vec2 aPos; // corresponds with attribute position 0
layout (location = 1) in vec4 aColor;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); // directly given to OpenGL, the normalized coordinates of the fucker
    // vertexColor = vec4(0.5, 0, 0, 1.); // red
    vertexColor = aColor;
}
