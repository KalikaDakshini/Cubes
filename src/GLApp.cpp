#include <iostream>

#include "GLApp.h"

#include <glm/glm.hpp>

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

  // Set context
  glfwMakeContextCurrent(this->_window);
  // Resize callback
  glfwSetFramebufferSizeCallback(this->_window, framebuffer_size_callback);
  // Keyboard callback
  glfwSetKeyCallback(this->_window, key_callback);
  glfwSetWindowUserPointer(this->_window, this);
  // Mouse callback
  glfwSetCursorPosCallback(this->_window, Camera::mouse_callback);
  glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

void GLApp::add_object(const std::string &filepath)
{
  Object *obj = new Object(filepath);
  this->_objects.push_back(obj);
}

// Main render loop
// ----------------
void GLApp::run()
{
  // Check graphic drivers
  std::cout << glGetString(GL_VENDOR) << "\n";
  std::cout << glGetString(GL_VERSION) << "\n";

  // Main loop of window
  float last_time = glfwGetTime();
  while (!glfwWindowShouldClose(this->_window)) {
    float cur_time = glfwGetTime();
    this->dt = cur_time - last_time;
    last_time = cur_time;

    // Transform Objects here
    this->_objects[0]->rotate(glm::vec3(0.5, 1.0, 0), 50.0 / 60.0);

    // Render objects
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

  this->_shader->use();
  // Set up perspective projection for 3D rendering
  glm::mat4 proj = glm::perspective(
    glm::radians(45.0f),
    (float)this->_width / (float)this->_height,
    0.1f,
    100.0f
  );
  glm::mat4 view = this->_cam.view();

  this->_shader->set_mat4("projection", proj);
  this->_shader->set_mat4("view", view);

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

void GLApp::on_key(
  int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods
)
{
  // Close window
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(this->_window, GLFW_TRUE);
  }
  // Camera movement
  if (key == GLFW_KEY_W) {
    this->_cam.move(FORWARD, this->dt);
  }
  if (key == GLFW_KEY_S) {
    this->_cam.move(BACKWARD, this->dt);
  }
  if (key == GLFW_KEY_A) {
    this->_cam.move(LEFT, this->dt);
  }
  if (key == GLFW_KEY_D) {
    this->_cam.move(RIGHT, this->dt);
  }
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
  auto *app = static_cast<GLApp *>(glfwGetWindowUserPointer(window));
  if (app) {
    app->on_key(key, scancode, action, mods);
  }
}

void GLApp::clear_objects()
{
  for (Object *obj : this->_objects) {
    delete obj;
  }
}
