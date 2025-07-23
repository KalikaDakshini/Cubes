#include <cstdlib>

#include "GLApp.h"

int main()
{
  GLApp app = GLApp(640, 480, "Test Window");

  // Initialise app
  if (!app.init()) {
    return EXIT_FAILURE;
  }

  std::vector<float> vertices{
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
  std::vector<unsigned int> indices{
    0,
    1,
    3,  // first triangle
    1,
    2,
    3  // second triangle
  };

  app.add_object(vertices, indices);

  // Run the application
  app.run();

  return EXIT_SUCCESS;
}
