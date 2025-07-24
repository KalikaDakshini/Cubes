#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
  ~Shader();

  /**
   * @brief Use the initialised shader program
   */
  void use() const;

  // Uniform Utility functions
  void set_float(const std::string &name, float value);
  void set_vec3(const std::string &name, glm::vec3 value);
};

#endif
