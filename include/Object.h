#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    glm::vec3 colour;

    Obj_spec(const std::string &filepath);
  };

  // Vertex data
  GLuint VAO, VBO, EBO;
  int index_count, vertex_count;

  // Visual data
  glm::vec3 _colour;

  // Orientation data
  glm::mat4 _transform;

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
  void draw(Shader &shader);

  /**
   * @brief Move the object along the distance vector
   */
  void move(glm::vec3 distance);

  /**
   * @brief Scale the object
   */
  void scale(glm::vec3 factor);

  /**
   * @brief Rotate the object about the axis
   *
   * @param angle in degrees
   */
  void rotate(glm::vec3 axis, float angle);
};

#endif
