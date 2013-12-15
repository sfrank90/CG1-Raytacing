#define SHEET 4
#define RESX 640                  // image x-resolution
#include "04/Renderer04.h"

/**
 * Main method. Use with "-refraction" or "-mirages".
 */
int main(int argc, char* argv[])
{
  Renderer04 re;

  // Task 4.1.
  if (argc >= 2 && !strcmp(argv[1], "-refraction"))
  {
    re.render("output/refraction.ppm", 4.1);
  }

  // Task 4.2.
  if (argc >= 2 && !strcmp(argv[1], "-spot"))
  {
    re.render("output/spot_light.ppm", 4.2);
  }

  // Task 4.3.
  else if (argc >= 2 && !strcmp(argv[1], "-mirages"))
  {
    re.render("output/mirages.ppm", 4.3);
  }

  // All.
  else
  {
    re.render("output/refraction.ppm", 4.1);
    re.render("output/spot_light.ppm", 4.2);
    // re.render("output/mirages.ppm", 4.3); // deactivated WS13/14.
  }
}