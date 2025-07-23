#include <iostream>

#include "GLApp.h"

// Constructor
GLApp::GLApp(int width, int height, const char *title) :
  _width(width),
  _height(height),
  _title(title),
  _window(nullptr),
  _shader(nullptr)
{}

// Destructor
GLApp::~GLApp()
{
  delete this->_shader;
  glfwTerminate();
}

// Initialise GLApp before running
bool GLApp::init()
{
  // Initialise GLFW
  // ---------------
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW\n";
    return false;
  }

  // Set minimum version of OpenGL
  // -----------------------------
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
  // ---------------
  this->_window = glfwCreateWindow(
    this->_width, this->_height, this->_title, nullptr, nullptr
  );
  if (!this->_window) {
    std::cerr << "Failed to create window\n";
    return false;
  }

  // Set context and callbacks
  glfwMakeContextCurrent(this->_window);
  glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
  glfwSetKeyCallback(this->_window, key_callback);

  // Load OpenGL functions with GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return false;
  }

  // Setup shaders
  try {
    this->_shader =
      new Shader("./src/shaders/shader.vert", "./src/shaders/shader.frag");
  } catch (const std::exception &err) {
    std::cerr << err.what() << "\n";
    return false;
  }

  return true;
}

// Main render loop
void GLApp::run()
{
  // Check graphic drivers
  std::cout << glGetString(GL_VENDOR) << "\n";
  std::cout << glGetString(GL_VERSION) << "\n";

  // ------------------------------------------------------------------
  float vertices[] = {
    0.5f,
    0.5f,
    0.0f,  // top right
    0.5f,
    -0.5f,
    0.0f,  // bottom right
    -0.5f,
    -0.5f,
    0.0f,  // bottom left
    -0.5f,
    0.5f,
    0.0f  // top left
  };
  unsigned int indices[] = {
    // note that we start from 0!
    0,
    1,
    3,  // first Triangle
    1,
    2,
    3  // second Triangle
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW
  );

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // remember: do NOT unbind the EBO while a VAO is active as the bound element
  // buffer object IS stored in the VAO; keep the EBO bound.
  //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);

  // Main loop of window
  while (!glfwWindowShouldClose(this->_window)) {
    // Render objects here
    this->render();

    // Draw the triangle
    this->_shader->use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap buffers and register events
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
  }
}

// --- Private Functions --- //
// Resize Callback function
void GLApp::framebuffer_size_callback(
  [[maybe_unused]] GLFWwindow *window, int width, int height
)
{
  glViewport(0, 0, width, height);
}

// Key Callback function
void GLApp::key_callback(
  GLFWwindow *window,
  int key,
  [[maybe_unused]] int scancode,
  int action,
  [[maybe_unused]] int mods
)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

// Render objects to screen
void GLApp::render()
{
  glClearColor(0.36F, 0.82F, 0.98F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
