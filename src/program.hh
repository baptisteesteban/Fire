#ifndef PROGRAM_HH
# define PROGRAM_HH

# include <string>

# include <GL/glew.h>

class program
{
public:
  program(const std::string& vertex_filename,
	  const std::string& fragment_filename,
	  const std::string& geometry_filename = "");
  ~program();
  void use();

  void setUniformui(GLuint e, const std::string& name);
  void setUniformi(GLint e, const std::string& name);
  void setUniformf(GLfloat e, const std::string& name);
  
private:
  GLuint program_;
};

#endif /* !PTOGRAM_HH */
