#ifndef GLAPP_H
#define GLAPP_H

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <vector>

#include "Object.h"
#include "Shader.h"

class GLApp
{
  int _width;
  int _height;
  const char *_title;
  GLFWwindow *_window;
  Shader *_shader;
  std::vector<Object *> _objects;

  /**
   * @brief Callback function for resizing
   *
   * @param window Window object
   * @param width Width of the window
   * @param height height of the window
   */
  static void
  framebuffer_size_callback(GLFWwindow *window, int width, int height);

  /**
   * @brief Callback function for key press
   */
  static void
  key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

  // TODO(kalika): Make this a seperate class
  /**
   * @brief Render objects to screen
   */
  void render();

  /**
   * @brief Delete all object pointers
   */
  void clear_objects();

public:
  GLApp(int width, int height, const char *title = "My Window");
  ~GLApp();

  /**
   * @brief Initialise GLApp before using it. Should be run before any other
   * function.
   *
   * @return true if initialisation is a success
   * @return false if initailisation step fails
   */
  bool init();

  /**
   * @brief Main loop of the progrm
   */
  void run();

  /**
   * @brief Add an object to render list
   */
  void add_object(Object *obj);
};

#endif
