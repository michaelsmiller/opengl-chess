#include "graphics/glad/glad.h" // generated file that deals with OpenGL for us theoretically
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <assert.h>

#include <util/types.h>
#include <util/util.h>
#include "shader.h"

static char buf[512]; // for error messages

Shader::Shader(const GLenum shader_type, const char * filename) : type(shader_type) {
  std::ifstream file;
  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    file.open(filename);
    if (!file.is_open()) ERROR("Could not open: %s", filename); 

    // get size of file
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    char * buffer = new char[length]; // allocate buffer
    file.read(buffer, length);
    file.close();
;
    // shader shit with buffer
    id = glCreateShader(shader_type);
    glShaderSource(id, 1, &buffer, NULL);
    delete[] buffer;
    glCompileShader(id);

    // check if compilation successful
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(id, 512, NULL, buf);
      ERROR("Failed to compile shader %s:\n%s", filename, buf);
    }
  }
  catch (const std::ifstream::failure & e) {
    ERROR("Could not read shader: %s", filename);
  }
}

ShaderProgram::ShaderProgram(const int n, const GLenum * types, const char * pathnames[]) {
  // compile all shaders
  for (int i = 0; i < n; i++) {
    Shader shader(types[i], pathnames[i]);
    shaders.push_back(shader);
  }
  assert(n > 0);
  assert(shaders[0].type == GL_VERTEX_SHADER);

  // create program
  id = glCreateProgram();
  for (int i = 0; i < n; i++) {
    glAttachShader(id, shaders[i].id);
  }
  // Finally, link the shaders
  glLinkProgram(id);
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, buf);
    ERROR("Shader linking error for shaders:\n%s", buf);
  }

  for (int i = 0; i < n; i++) {
    glDeleteShader(shaders[i].id);
  }
}

void
ShaderProgram::use() const {
  glUseProgram(id); // need to do this to ensure the correct program is being used
}

void
ShaderProgram::setFloat(const char * name, float t) const {
  glUniform1f(glGetUniformLocation(id, name), t);
}

void
ShaderProgram::setInt(const char * name, int t) const {
  glUniform1i(glGetUniformLocation(id, name), t);
}

void
ShaderProgram::setBool(const char * name, bool t) const {
  setInt(name, (int)t);
}
