#include <vector>

#include "particles.hh"

particles::particles()
  : p_("../shaders/particle.vert", "../shaders/particle.frag", "../shaders/particle.geom")
  , dt_(0)
{
  std::vector<GLfloat> pos = {0.0f, 0.0f, 0.0f};
  
  glGenVertexArrays(1, &vao_);
  GLuint vbo;
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(GLfloat), &pos[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
  glPointSize(20);
}

void
particles::draw()
{
  p_.use();
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, 3);
}

void
particles::update()
{
  dt_ += 0.05f;
  if (dt_ > 0.70f)
    dt_ = 0.0f;

  p_.setUniformf(dt_, "dt");
}
