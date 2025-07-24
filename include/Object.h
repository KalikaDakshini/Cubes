#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <glm/glm.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "Shader.h"

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;

class Object
{
  class Obj_spec
  {
  public:
    Vertices vertices;
    Indices indices;
    glm::vec3 position;
    glm::vec3 colour;

    Obj_spec(const std::string &filepath);
  };

  // Vertex data
  GLuint VAO, VBO, EBO;
  int index_count, vertex_count;

  // Orientation data
  glm::vec3 _position;

  // Visual data
  glm::vec3 _colour;

  // Constructor
  Object(const Obj_spec &spec);

  // Load Object data into GPU's memory
  void load_object(const Vertices &vertices, const Indices &indices);

public:
  Object(const std::string &filepath);
  ~Object();

  /**
   * @brief Draw object using GL functions and the shader provided
   *
   * @param shader Shader program used to draw
   */
  void draw(Shader &shader) const;
};

#endif
