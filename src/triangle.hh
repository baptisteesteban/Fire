#ifndef TRIANGLE_HH
# define TRIANGLE_HH

# include <GL/glew.h>
# include <vector>

# include "program.hh"

class triangle
{
public:
  triangle(const std::vector<GLfloat>& pos);
  void draw(void);

private:
  GLuint vao_;
  program p_;
};

#endif /* !TRIANGLE_HH */
