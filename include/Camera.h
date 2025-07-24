#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum Cam_dir { FORWARD, BACKWARD, LEFT, RIGHT, NUM_DIRS };

class Camera
{
  // Position of camera
  glm::vec3 _pos;
  // Co-ordinate system
  glm::vec3 _front, _up, _right;
  glm::vec3 _world_up;
  // Viewing angles
  float _yaw, _pitch;

  // Mouse movement options
  float _speed, _rot_speed;
  float _last_xpos, _last_ypos;
  bool _first_mouse;

  /**
   * @brief Update camera co-ordinate system after rotation
   */
  void update_vectors();

  static Camera *active_instance;

public:
  Camera(glm::vec3 position = glm::vec3(0, 0, 3.0f));

  /**
   * @brief Return the view matrix of the camer
   */
  glm::mat4 view();

  /**
   * @brief Move the camera along direction
   */
  void move(Cam_dir dir, float dt);

  /**
   * @brief Callback function for mouse movement
   */
  static void mouse_callback(GLFWwindow *window, double x_pos, double y_pos);

  /**
   * @brief Process mouse movement
   */
  void process_mouse_movement(float xpos, float ypos);
};

#endif
