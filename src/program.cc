#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "program.hh"

program::program(const std::string& vertex_filename,
		 const std::string& fragment_filename,
		 const std::string& geometry_filename)
{
  /* Read the files containing the shaders sources */
  std::ifstream in_vertex(vertex_filename);
  if (!in_vertex.is_open())
    throw std::invalid_argument("Could not open vertex shader source file");
  std::ifstream in_fragment(fragment_filename);
  if (!in_fragment.is_open())
    throw std::invalid_argument("Could not open fragment shader source file");

  std::ifstream in_geom;
  if (geometry_filename.size() > 0)
  {
    in_geom = std::ifstream(geometry_filename);
    if (!in_geom.is_open())
      throw std::invalid_argument("Could not open geometry shader source file");
  }

  std::stringstream ss_geom;
  std::stringstream ss_vertex;
  std::stringstream ss_fragment;
  ss_vertex << in_vertex.rdbuf();
  ss_fragment << in_fragment.rdbuf();

  if (geometry_filename.size() > 0)
    ss_geom << in_geom.rdbuf();
  
  std::string vertex_src_string = ss_vertex.str();
  std::string fragment_src_string = ss_fragment.str();
  std::string geom_src_string;
  if (geometry_filename.size() > 0)
    geom_src_string = ss_geom.str();
  
  const GLchar* vertex_src = (const GLchar*)vertex_src_string.c_str();
  const GLchar* fragment_src = (const GLchar*)fragment_src_string.c_str();
  const GLchar* geom_src = NULL;
  if (geometry_filename.size() > 0)
    geom_src = (const GLchar*)geom_src_string.c_str();
    
  /* Creation of the shaders */
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint geom_shader;
  if (geometry_filename.size() > 0)
    geom_shader = glCreateShader(GL_GEOMETRY_SHADER);
    
  /* Give the sources at each shaders */
  glShaderSource(vertex_shader, 1, &vertex_src, NULL);
  glShaderSource(fragment_shader, 1, &fragment_src, NULL);
  if (geometry_filename.size() > 0)
    glShaderSource(geom_shader, 1, &geom_src, NULL);
  
  GLint isCompiled = 0;

  /* Compilation of the vertex shader and error handling of the compilation*/
  glCompileShader(vertex_shader);
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar log[maxLength];
    glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &log[0]);

    glDeleteShader(vertex_shader);
      
    throw std::invalid_argument(vertex_filename + ": " + log);
  }

  /* Compilation of the fragment shader and error handling */
  glCompileShader(fragment_shader);
  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar log[maxLength];
    glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &log[0]);

    glDeleteShader(fragment_shader);
      
    throw std::invalid_argument(fragment_filename + ": " + log);
  }

  /* Compilation of geometry shader */
  if (geometry_filename.size() > 0)
  {
    glCompileShader(geom_shader);
    glGetShaderiv(geom_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetShaderiv(geom_shader, GL_INFO_LOG_LENGTH, &maxLength);
      
      GLchar log[maxLength];
      glGetShaderInfoLog(geom_shader, maxLength, &maxLength, &log[0]);
      
      glDeleteShader(geom_shader);
      
      throw std::invalid_argument(geometry_filename + ": " + log);
    }
  }

  program_ = glCreateProgram();
  glAttachShader(program_, vertex_shader);
  if (geometry_filename.size() > 0)
    glAttachShader(program_, geom_shader);
  glAttachShader(program_, fragment_shader);

  glLinkProgram(program_);
    
  GLint isLinked = 0;
  glGetProgramiv(program_, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar log[maxLength];
    glGetProgramInfoLog(program_, maxLength, &maxLength, &log[0]);

    glDeleteProgram(program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (geometry_filename.size() > 0)
      glDeleteShader(geom_shader);

    throw std::runtime_error("Could not link the program shader : " + std::string(log));
  }
  glDetachShader(program_, vertex_shader);
  glDetachShader(program_, fragment_shader);
  if (geometry_filename.size() > 0)
    glDetachShader(program_, geom_shader);
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
  if (geometry_filename.size() > 0)
    glDeleteShader(geom_shader);
}

program::~program()
{
  glDeleteProgram(program_);
}

void
program::use()
{
  glUseProgram(program_);
}


void
program::setUniformui(GLuint e, const std::string& name)
{ 
  GLint loc = glGetUniformLocation(program_, name.c_str());
  glUniform1ui(loc, e);
}

void
program::setUniformi(GLint e, const std::string& name)
{
  GLint loc = glGetUniformLocation(program_, name.c_str());
  glUniform1i(loc, e);
}

void
program::setUniformf(GLfloat e, const std::string& name)
{
  GLint loc = glGetUniformLocation(program_, name.c_str());
  glUniform1f(loc, e);
}
