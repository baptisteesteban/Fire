#ifndef PROGRAM_HH
# define PROGRAM_HH

# include <string>

# include <GL/glew.h>

class program
{
public:
  program(const std::string& vertex_filename, const std::string& fragment_filename);
  ~program();
  void use();
  
private:
  GLuint program_;
};

#endif /* !PTOGRAM_HH */
