#ifndef PARTICLES_HH
# define PARTICLES_HH

# include <vector>

# include <GL/glew.h>

# include "program.hh"

struct particle
{
  particle()
    : pos({0.0f, 0.0f, 0.0f})
    , life(1.0f)
    , speed(0.0f)
    , dir({0.0f, 0.0f, 0.0f})
    {}
  
  GLfloat pos[3];
  GLfloat life;
  GLfloat speed;
  GLfloat dir[3];
};

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
  std::vector<particle> parts_;
};

#endif /* !PARTICLES_HH */
