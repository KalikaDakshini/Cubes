#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "Shader.h"

class Object
{
  GLuint VAO, VBO, EBO;
  int index_count, vertex_count;

  // Load Object data into GPU's memory
  void
  load_object(std::vector<float> &vertices, std::vector<unsigned int> &indices);

public:
  Object(std::vector<float> &vertices, std::vector<unsigned int> &indices);
  ~Object();

  void draw(const Shader &shader) const;
};

#endif
