#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;

struct Obj_spec {
  const Vertices &vertices;
  const Indices &indices;
  const glm::vec3 position;
  const glm::vec3 colour;

  Obj_spec(
    const Vertices &v,
    const Indices &i,
    glm::vec3 pos = glm::vec3(0, 0, 0),
    glm::vec3 clr = glm::vec3(1, 1, 1)
  ) :
    vertices(v), indices(i), position(pos), colour(clr)
  {}
};

class Object

{
  // Vertex data
  GLuint VAO, VBO, EBO;
  int index_count, vertex_count;

  // Orientation data
  glm::vec3 _position;

  // Visual data
  glm::vec3 _colour;

  // Load Object data into GPU's memory
  void load_object(const Vertices &vertices, const Indices &indices);

public:
  Object(const Obj_spec &spec);
  ~Object();

  /**
   * @brief Draw object using GL functions and the shader provided
   *
   * @param shader Shader program used to draw
   */
  void draw(Shader &shader) const;
};

#endif
