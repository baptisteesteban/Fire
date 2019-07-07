#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "particles.hh"

/*
 * From https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624
 */
float RandomFloat(float min, float max)
{
  float random = ((float) rand()) / (float) RAND_MAX;
  float range = max - min;  
  return (random*range) + min;
}

particles::particles(const GLuint nb_particles)
  : nb_particles_(nb_particles)
  , p_("../shaders/particle.vert", "../shaders/particle.frag", "../shaders/particle.geom")
  , dt_(0)
{
  srand(time(NULL));
  
  glGenVertexArrays(1, &vao_);
  GLuint vbo[2];
  glGenBuffers(2, vbo);
  
  glBindVertexArray(vao_);
  
  /* Position VBO */
  std::vector<GLfloat> pos(nb_particles_ * 3);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(GLfloat), &pos[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  /*Directional vectors */
  std::vector<GLfloat> dir(nb_particles_ * 3);
  for (std::size_t i = 0; i < nb_particles_; i++)
  {
    dir[i * 3] = RandomFloat(0.0f, 0.03f);
    dir[i * 3 + 1] = RandomFloat(0.02f, 0.05f);
    dir[i * 3 + 2] = 0;
  }

  
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, dir.size() * sizeof(GLfloat), &dir[0], GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(1);
 
}

void
particles::draw()
{ 
  p_.use();
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, nb_particles_);
}

void
particles::update()
{
  if (dt_ > 20)
    dt_ = 0;
  dt_ += 1;
  p_.setUniformui(dt_, "dt");
}
