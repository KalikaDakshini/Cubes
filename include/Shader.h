#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>

class Shader
{
  GLuint prog_id;

  /**
   * @brief Check for compilation errors
   * @param object Object being processed
   * @param shader if true, check shader, else check linker
   * @return true if success, false on errors
   */
  static void check_errors(GLuint object, bool shader);

  /**
   * @brief Load shader from text file
   * @param path Path to text file
   * @return Shader code as a string
   */
  static std::string load_shader(const std::string &path);

public:
  Shader(const std::string &vert_file, const std::string &frag_file);

  /**
   * @brief Use the initialised shader program
   */
  void use() const;
};

#endif
