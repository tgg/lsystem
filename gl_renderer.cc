#include <GL/gl.h>

#include <algorithm>
#include <utility>
#include <cmath>

#include "gl_renderer.hh"

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
    angle_ -= 0.0f;
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
