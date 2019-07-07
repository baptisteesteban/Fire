#include <iostream>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "particles.hh"

bool init_glew()
{
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    std::cerr << "Glew init: " << glewGetErrorString(err) << std::endl;
    return false;
  }
  return true;
}

void init_gl()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_PROGRAM_POINT_SIZE);
}

int main(int argc, char *argv[])
{
  // Initialization of the SDL
  constexpr std::size_t w_width = 1000;
  constexpr std::size_t w_height = 800;
  SDL_Window *window = SDL_CreateWindow("OpenGL Fire", 0, 0, w_width, w_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window)
  {
    std::cerr << "SDL: Could not create window" << std::endl;
    return 1;
  }
  
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!init_glew())
    return 1;
  init_gl();

  // Initialization of the object
  auto fire = particles(1000);
  
  // Program loop
  bool running = true;
  while(running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	running = false;
    }

    /* OPENGL Part */
    glClear(GL_COLOR_BUFFER_BIT);

    fire.draw();
    fire.update();
    
    glFlush();
    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  
  return 0;
}
