#ifndef PARTICLES_HH
# define PARTICLES_HH

# include <vector>

# include <GL/glew.h>

# include "program.hh"

class particles
{
public:
  particles(const GLuint nb_particles);
  void draw();
  void update();

private:
  const GLuint nb_particles_;
  program p_;
  GLuint vao_;
  GLuint dt_;
};

#endif /* !PARTICLES_HH */
