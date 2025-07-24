#include <cstdlib>

#include "GLApp.h"

int main()
{
  GLApp app = GLApp(640, 480, "Test Window");

  // Initialise app
  if (!app.init()) {
    return EXIT_FAILURE;
  }

  app.add_object("./data/objects/triangle.conf");

  // Run the application
  app.run();

  return EXIT_SUCCESS;
}
