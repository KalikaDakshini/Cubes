#include "Object.h"

// Constructor
Object::Object(std::vector<float> &vertices, std::vector<unsigned int> &indices)
{
  this->load_object(vertices, indices);
}

// Destructor
Object::~Object()
{
  glDeleteBuffers(1, &(this->EBO));
  glDeleteBuffers(1, &(this->VBO));
  glDeleteVertexArrays(1, &(this->VAO));
}

// Draw object once loaded
void Object::draw(const Shader &shader) const
{
  shader.use();
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, 0);
}

// -------- Private Functions -------- //
void Object::load_object(
  std::vector<float> &vertices, std::vector<unsigned int> &indices
)
{
  // Record array sizes for later use
  this->index_count = indices.size();
  this->vertex_count = vertices.size();

  //Generate buffers and vertex arrays
  glGenVertexArrays(1, &(this->VAO));
  glGenBuffers(1, &(this->VBO));
  glGenBuffers(1, &(this->EBO));

  // Bind buffers and vertex arrays
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

  // Push data into buffers
  glBufferData(
    GL_ARRAY_BUFFER,
    this->vertex_count * sizeof(float),
    vertices.data(),
    GL_STATIC_DRAW
  );
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    indices.size() * sizeof(unsigned int),
    indices.data(),
    GL_STATIC_DRAW
  );

  // Set and enable Vertex pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}
