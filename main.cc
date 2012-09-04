#include <iostream>

#include "lsystem.hh"
#include "renderer_config.hh"
#include "gl_renderer.hh"


///////////////////////////////////////////////////////////////////////////////
// MAIN
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
  /*
  rule_map koch_rules = { { 'F', "F+F-F-F+F" } };
  lsystem koch("F", koch_rules);
  renderer_config koch_config(1, -90, 90, 0,
			      std::make_pair(-70.0f, -70.0f),
			      std::make_pair(0.5f, 0.5f));
  renderer = new gl_renderer(koch, koch_config);
  */

  rule_map rules = { { 'X', "F-[[X]+X]+F[+FX]-X" },
		     { 'F', "FF" } };
  lsystem system("X", rules);

  renderer_config config(1, 25.f, -25.f, 70.f,
			 std::make_pair(-50.f, -50.f),
			 std::make_pair(0.5f, 0.5f));

  gl_renderer renderer(system, config);
  renderer.init(argc, argv);
  renderer.run();

  return EXIT_SUCCESS;
}
