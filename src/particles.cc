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

particles::particles()
  : p_("../shaders/particle.vert", "../shaders/particle.frag", "../shaders/particle.geom")
{
  srand(time(NULL));
  
  glGenVertexArrays(1, &vao_);
}

void
particles::draw()
{
  p_.use();
  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, particles_.size());
}

void
particles::update()
{
  for (auto it = particles_.begin(); it != particles_.end(); it++)
  {
    /* Delete old particles */
    if (it->life <= 0.0f)
      particles_.erase(it);
    
    /* Update particles */
    it->pos[0] += it->dt * it->dir[0];
    it->pos[1] += it->dt * it->dir[1];
    it->pos[2] += it->dt * it->dir[2];
    it->life -= 0.05f;
  }
  /* Generate particles */
  for (int i = 0; i < 1000; i++)
    particles_.push_back(particle());

  /* Create VBO */
  std::vector<GLfloat> pos;
  for (auto it = particles_.begin(); it != particles_.end(); it++)
  {
    pos.push_back(it->pos[0]);
    pos.push_back(it->pos[1]);
    pos.push_back(it->pos[2]);
  }
  
   GLuint vbo;
  glGenBuffers(1, &vbo);
  
  glBindVertexArray(vao_);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(GLfloat), &pos[0], GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
}
