#include <cstdlib>

#include "GLApp.h"

int main()
{
  GLApp app = GLApp(640, 480, "Test Window");

  // Initialise app
  if (!app.init()) {
    return EXIT_FAILURE;
  }

  // Run the application
  app.run();

  return EXIT_SUCCESS;
}
