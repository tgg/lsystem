#include <GL/gl.h>
#include <GL/glut.h>

#include <functional>
#include <algorithm>
#include <utility>
#include <cmath>

#include "gl_renderer.hh"

// !!! Hackish !!!
// GLUT to gl_renderer methods routing
// the functions are bound in the init method
static std::function<void()> renderer_render;
static std::function<void(int, int, int, int)> renderer_mouse_evt;
static std::function<void(GLsizei, GLsizei)> renderer_reshape;

static void mouseFunc(int button, int state, int x, int y)
{
  renderer_mouse_evt(button, state, x, y);
}

static void reshapeFunc(GLsizei width, GLsizei height)
{
  renderer_reshape(width, height);
}

static void displayFunc()
{
  renderer_render();
}

///////////////////////////////////////////////////////////////////////////////
// GL RENDERER IMPLEMENTATION
///////////////////////////////////////////////////////////////////////////////
void
gl_renderer::init(int argc, char* argv[])
{
  using namespace std::placeholders;

  // Bind global funcs to private member methods
  renderer_render = std::bind(&gl_renderer::render, this);
  renderer_mouse_evt = std::bind(&gl_renderer::mouse_evt, this, _1, _2, _3, _4);
  renderer_reshape = std::bind(&gl_renderer::reshape, this, _1, _2);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(800, 800);
  glutCreateWindow("LSystem");

  glutMouseFunc(mouseFunc);
  glutReshapeFunc(reshapeFunc);
  glutDisplayFunc(displayFunc);
}

void
gl_renderer::run()
{
  glutMainLoop();
}

void 
gl_renderer::reshape(GLsizei width, GLsizei height)
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

void 
gl_renderer::mouse_evt(int, int state, int, int)
{
  if(GLUT_DOWN == state)
    render();
}

void
gl_renderer::render()
{
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,
	      GL_ONE_MINUS_SRC_ALPHA);
  glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);

  // TODO should be in config
  glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  
  // Change origin and scaling
  glTranslatef(config_.translation().first,
	       config_.translation().second,
	       0.0f);

  glScalef(config_.scale().first,
	   config_.scale().second,
	   0.0f);

  // TODO should be in config
  glColor3f(0.0f, 0.8f, 0.2f);

  // Draw next generation
  render_system();

  glPopMatrix();
  glFlush();
}

void
gl_renderer::render_system()
{
  x_ = y_ = 0.0f;
  angle_ = config_.initial_angle();

  auto current = system_.evolve();
  std::for_each(current.begin(), current.end(),
		[&](char c)
		{
		  switch(c)
		    {
		    case 'F': 
		      forward();
		      break;
		    case '+':
		      rotate(config_.right_angle());
		      break;
		    case '-':
		      rotate(config_.left_angle());
		      break;
		    case '[':
		      push_state();
		      break;
		    case ']':
		      pop_state();
		      break;
		    }
		});
}

void 
gl_renderer::forward()
{
  float x1 = x_ + config_.segment_length() * cos(angle_ * (M_PI / 180.0f));
  float y1 = y_ + config_.segment_length() * sin(angle_ * (M_PI / 180.0f));

  glBegin(GL_LINES);
  glVertex2f(x_, y_);
  glVertex2f(x1, y1);
  glEnd();

  x_ = x1;
  y_ = y1;
}

void
gl_renderer:: rotate(float angle)
{
  angle_ += angle;

  if(angle_ >= 360.0f)
    angle_ -= 360.0f;

  if(angle_ < 0.0f)
    angle_ += 360.0f;
}

void
gl_renderer::push_state()
{
  auto state = std::make_tuple(x_, y_, angle_);
  state_.push(state);
}

void
gl_renderer::pop_state()
{
  std::tie(x_, y_, angle_) = state_.top();
  state_.pop();
}
