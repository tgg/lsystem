#ifndef GL_RENDERER_HH
#define GL_RENDERER_HH

#include <GL/gl.h>

#include <stack>
#include <tuple>

#include "lsystem.hh"
#include "renderer_config.hh"

class gl_renderer
{
public:
  gl_renderer(lsystem& system, renderer_config& config)
    : system_(system), config_(config)
  {}

  void init(int argc, char* argv[]);
  void run();

private:
  void render_system();
  void forward();
  void rotate(float angle);
  void push_state();
  void pop_state();

  // GLUT event functions
  void mouse_evt(int, int, int, int);
  void reshape(GLsizei, GLsizei);
  void render();

private:
  lsystem system_;
  renderer_config config_;
  std::stack<std::tuple<float, float, float>> state_;
  float x_, y_, angle_;
};

#endif // GL_RENDERER_HH
