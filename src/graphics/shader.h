#ifndef SHADER_H_
#define SHADER_H_

#include <vector>
#include <string>
#include <util/types.h>

class Shader {
public:
  glid id;
  const GLenum type;

public:
  Shader(const GLenum type, const char * path);
};


class ShaderProgram {
  private:
    glid id;
    std::vector<Shader> shaders;

  public:
    // Calls Shader() a bunch and checks that first shader is a vertex shader
    ShaderProgram(const int n, const GLenum * types, const char * pathnames[]);
    void use() const; // has OpenGL enable the shader program

    void setFloat(const char * name, float t) const;
    void setInt  (const char * name, int t)   const;
    void setBool (const char * name, bool t)  const;
};

#endif
