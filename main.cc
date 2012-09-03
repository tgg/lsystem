#include <iostream>

#include <GL/glut.h>

#include "lsystem.hh"
#include "renderer_config.hh"
#include "gl_renderer.hh"

///////////////////////////////////////////////////////////////////////////////
// GL RENDERER
///////////////////////////////////////////////////////////////////////////////
static gl_renderer* renderer;

///////////////////////////////////////////////////////////////////////////////
// GLUT UI FUNCTIONS
///////////////////////////////////////////////////////////////////////////////
static void ui_display()
{
  renderer->render();
}

static void ui_reshape(GLsizei width, GLsizei height)
{
  GLfloat aspect_ratio;
  if (height == 0)
    height = 1;
        
  glViewport(0, 0, width, height);
        
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
        
  aspect_ratio = (GLfloat)width / (GLfloat)height;
  if (width <= height)
    glOrtho (-100.0, 100.0,
             -100 / aspect_ratio, 100.0 / aspect_ratio,
             1.0, -1.0);
  else
    glOrtho(-100.0 * aspect_ratio, 100.0 * aspect_ratio, 
            -100.0, 100.0, 
            1.0, -1.0);
        
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void ui_mouse(int, int state, int, int)
{
  if(GLUT_DOWN == state)
    ui_display();
}

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
  renderer = new gl_renderer(system, config);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(800, 800);
  glutCreateWindow("LSystem");
  glutMouseFunc(ui_mouse); 
  glutReshapeFunc(ui_reshape);
  glutDisplayFunc(ui_display);

  glutMainLoop();

  delete renderer;

  return EXIT_SUCCESS;
}
