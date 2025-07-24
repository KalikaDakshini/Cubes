#include <cstdlib>

#include "GLApp.h"

int main()
{
  GLApp app = GLApp(900, 900, "Test Window");

  // Initialise app
  if (!app.init()) {
    return EXIT_FAILURE;
  }

  app.add_object("./data/objects/cube.conf");

  // Run the application
  app.run();

  return EXIT_SUCCESS;
}
