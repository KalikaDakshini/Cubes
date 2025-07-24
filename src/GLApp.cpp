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
  if (!glfwInit()) {
    std::cerr << "Failed to initialise GLFW\n";
    return false;
  }

  // Set minimum version of OpenGL
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
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

void GLApp::add_object(const Obj_spec &spec)
{
  Object *obj = new Object(spec);
  this->_objects.push_back(obj);
}

// Main render loop
void GLApp::run()
{
  // Check graphic drivers
  std::cout << glGetString(GL_VENDOR) << "\n";
  std::cout << glGetString(GL_VERSION) << "\n";

  // Main loop of window
  while (!glfwWindowShouldClose(this->_window)) {
    // Render objects here
    this->render();

    // Swap buffers and register events
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
  }

  // Free memory used by objects
  this->clear_objects();
}

// -------- Private Functions -------- //
// Render objects to screen
void GLApp::render()
{
  glClearColor(0.36F, 0.82F, 0.98F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw objects
  for (Object *obj : this->_objects) {
    obj->draw(*(this->_shader));
  }
}

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

void GLApp::clear_objects()
{
  for (Object *obj : this->_objects) {
    delete obj;
  }
}
