#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "triangle.hh"

triangle::triangle(const std::vector<GLfloat>& pos)
  : p_("../shaders/triangle.vert", "../shaders/triangle.frag")
{
  if (pos.size() != 9)
    throw std::invalid_argument("Triangle: pos should have a size of 9 floats");
  
  glGenVertexArrays(1, &vao_);
  GLuint vbo;
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof (GLfloat), pos.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);
}

void
triangle::draw(void)
{
  p_.use();
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
