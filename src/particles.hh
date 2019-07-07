#ifndef PARTICLES_HH
# define PARTICLES_HH

# include <vector>

# include <GL/glew.h>

# include "program.hh"

float RandomFloat(float min, float max);

struct particle
{
  particle()
    {
      pos[0] = 0.0f;
      pos[1] = -0.90f;
      pos[2] = 0.0f;

      dir[0] = RandomFloat(0.0f, 0.05f);
      dir[1] = RandomFloat(0.1f, 0.5f);
      dir[2] = 0.0f;

      dt = 0.025;
      life = 1.0f;
    }
  
  GLfloat pos[3];
  GLfloat dir[3];
  GLfloat dt;
  GLfloat life;
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
  std::vector<particle> particles_;
};

#endif /* !PARTICLES_HH */
