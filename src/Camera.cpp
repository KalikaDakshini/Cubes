#include "Camera.h"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera *Camera::active_instance = nullptr;

Camera::Camera(glm::vec3 pos) :
  _pos(pos),
  _front(glm::vec3(0, 0, -1)),
  _up(glm::vec3(0, 1, 0)),
  _world_up(_up),
  _yaw(-90.0f),
  _pitch(0.0f),
  _speed(3.0f),
  _rot_speed(1.0f),
  _last_xpos(0.0f),
  _last_ypos(0.0f),
  _first_mouse(true)
{
  this->update_vectors();
  active_instance = this;
}

// Return the view matrix
glm::mat4 Camera::view()
{
  return glm::lookAt(this->_pos, this->_pos + this->_front, this->_up);
}

void Camera::move(Cam_dir dir, float dt)
{
  if (dir == FORWARD) {
    this->_pos += this->_front * (this->_speed * dt);
  }
  else if (dir == BACKWARD) {
    this->_pos -= this->_front * (this->_speed * dt);
  }
  else if (dir == RIGHT) {
    this->_pos += this->_right * (this->_speed * dt);
  }
  else {
    this->_pos -= this->_right * (this->_speed * dt);
  }
}

// Mouse callback function
void Camera::mouse_callback(
  [[maybe_unused]] GLFWwindow *window, double xpos, double ypos
)
{
  if (active_instance) {
    active_instance->process_mouse_movement(
      static_cast<float>(xpos), static_cast<float>(ypos)
    );
  }
}

// -------- Private functions -------- //
void Camera::update_vectors()
{
  // Calculate the front vector
  this->_front.x =
    cos(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
  this->_front.y = sin(glm::radians(this->_pitch));
  this->_front.z =
    sin(glm::radians(this->_yaw)) * cos(glm::radians(this->_pitch));
  this->_front = glm::normalize(this->_front);

  // Calculate the right and up using front
  this->_right = glm::normalize(glm::cross(this->_front, this->_world_up));
  this->_up = glm::normalize(glm::cross(this->_right, this->_front));
}

void Camera::process_mouse_movement(float xpos, float ypos)
{
  if (this->_first_mouse) {
    this->_last_xpos = xpos;
    this->_last_ypos = ypos;
    this->_first_mouse = false;
    return;
  }

  float xoffset = xpos - _last_xpos;
  float yoffset = _last_ypos - ypos;

  _last_xpos = xpos;
  _last_ypos = ypos;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  this->_yaw += xoffset;
  this->_pitch += yoffset;

  this->_pitch = std::clamp(this->_pitch, -89.0f, 89.0f);

  this->update_vectors();
}
