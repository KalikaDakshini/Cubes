#include "Shader.h"

// Constructor
Shader::Shader(const std::string &vert_file, const std::string &frag_file)
{
  // Load code from source files
  std::string vert_source = Shader::load_shader(vert_file);
  std::string frag_source = Shader::load_shader(frag_file);
  const char *vert_code = vert_source.c_str();
  const char *frag_code = frag_source.c_str();

  // Compile Vertex Shader
  GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, &vert_code, nullptr);
  glCompileShader(vert_shader);
  check_errors(vert_shader, true);

  // Compile Fragment Shader
  GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, &frag_code, nullptr);
  glCompileShader(frag_shader);
  check_errors(frag_shader, true);

  // Link shaders to program
  this->prog_id = glCreateProgram();
  glAttachShader(prog_id, vert_shader);
  glAttachShader(prog_id, frag_shader);
  glLinkProgram(prog_id);
  check_errors(this->prog_id, false);

  // Delete shaders
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);
}

// Destructor
Shader::~Shader()
{
  glDeleteShader(this->prog_id);
}

// Use the shader
void Shader::use() const
{
  glUseProgram(this->prog_id);
}

// Set a float
void Shader::set_float(const std::string &name, float value)
{
  glUniform1f(glGetUniformLocation(this->prog_id, name.c_str()), value);
}

// Set a vec3
void Shader::set_vec3(const std::string &name, glm::vec3 value)
{
  glUniform3f(
    glGetUniformLocation(this->prog_id, name.c_str()), value.x, value.y, value.z
  );
}

// Set a mat4
void Shader::set_mat4(const std::string &name, glm::mat4 value)
{
  glUniformMatrix4fv(
    glGetUniformLocation(this->prog_id, name.c_str()),
    1,
    GL_FALSE,
    glm::value_ptr(value)
  );
}

//-------- Private Functions -------- //
// Load shader file from source
std::string Shader::load_shader(const std::string &path)
{
  std::ifstream infile(path);
  if (!infile.is_open()) {
    throw std::runtime_error("Cannot open file: " + path);
  }
  std::stringstream ss;
  ss << infile.rdbuf();

  infile.close();
  return ss.str();
}

// Check for compiltion errors in shader and linker
void Shader::check_errors(GLuint object, bool shader)
{
  int success;
  char infoLog[512];

  // Check for shader compilation errors
  if (shader) {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 512, NULL, infoLog);
      throw std::runtime_error(
        "ERROR::SHADER_COMPILATION_FAILED\n" + std::string(infoLog)
      );
    }
  }

  // Check for linker errors
  else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 512, NULL, infoLog);
      throw std::runtime_error(
        "ERROR::PROGRAM_LINKING_FAILED\n" + std::string(infoLog)
      );
    }
  }
}
