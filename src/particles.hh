#ifndef PARTICLES_HH
# define PARTICLES_HH

# include <GL/glew.h>

# include "program.hh"

class particles
{
public:
  particles();
  void draw();
  void update();

private:
  program p_;
  GLuint vao_;
  GLfloat dt_;
};

#endif /* !PARTICLES_HH */
