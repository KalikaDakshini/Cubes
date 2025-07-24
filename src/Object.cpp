#include "Object.h"

// Object Spec functions
// ---------------------
Object::Obj_spec::Obj_spec(const std::string &filepath)
{
  std::cout << "Reading file " << filepath << std::endl;

  std::ifstream infile(filepath);
  if (!infile.is_open()) {
    throw std::runtime_error("Cannot open file: " + filepath);
  }

  std::string line;
  while (std::getline(infile, line)) {
    // Skip whitespace and comments
    line.erase(0, line.find_first_not_of(" \t\r\n"));
    line.erase(line.find_last_not_of(" \t\r\n") + 1);
    if (line.empty() || line[0] == '#') {
      continue;
    }

    // Get keyword
    std::stringstream ss(line);
    std::string keyword;
    ss >> keyword;

    // Read vertices
    if (keyword == "verts") {
      int count;
      ss >> count;
      for (int i = 0; i < count; ++i) {
        float x, y, z;
        infile >> x >> y >> z;
        vertices.insert(vertices.end(), {x, y, z});
      }
    }
    // Read indices
    else if (keyword == "indices") {
      int count;
      ss >> count;
      for (int i = 0; i < count; ++i) {
        unsigned int a, b, c;
        infile >> a >> b >> c;
        indices.insert(indices.end(), {a, b, c});
      }
    }
    // Read colour
    else if (keyword == "colour") {
      float r, g, b;
      ss >> r >> g >> b;
      colour = glm::vec3(r, g, b);
    }
    // Report error
    else {
      std::cerr << "Unknown keyword: " << keyword << '\n';
    }
  }

  infile.close();
}

// Object Functions
// ----------------
// Constructor
Object::Object(const std::string &filepath) : Object(Obj_spec(filepath))
{}

// Destructor
Object::~Object()
{
  glDeleteBuffers(1, &(this->EBO));
  glDeleteBuffers(1, &(this->VBO));
  glDeleteVertexArrays(1, &(this->VAO));
}

// Draw object once loaded
void Object::draw(Shader &shader)
{
  // Link shader and load values
  shader.use();
  shader.set_vec3("objColour", this->_colour);
  shader.set_mat4("transform", this->_transform);

  // Draw object
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, 0);
}

// Move the object to new position
void Object::move(glm::vec3 distance)
{
  this->_transform = glm::translate(this->_transform, distance);
}

// Scale the object by desired factor
void Object::scale(glm::vec3 factor)
{
  this->_transform = glm::scale(this->_transform, factor);
}

// Rotate the object by an angle at the axis
void Object::rotate(glm::vec3 axis, float angle)
{
  axis = glm::normalize(axis);
  this->_transform = glm::rotate(this->_transform, glm::radians(angle), axis);
}

// -------- Private Functions -------- //
// Constructor
Object::Object(const Obj_spec &spec) :
  _transform(glm::mat4(1.0f)), _colour(spec.colour)
{
  this->load_object(spec.vertices, spec.indices);
}

void Object::load_object(const Vertices &vertices, const Indices &indices)
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
