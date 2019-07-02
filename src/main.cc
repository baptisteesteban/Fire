#include <iostream>

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


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
}

int main(int argc, char *argv[])
{
  constexpr std::size_t w_width = 1000;
  constexpr std::size_t w_height = 800;
  SDL_Window *window = SDL_CreateWindow("OpenGL Fire", 0, 0, w_width, w_height, SDL_WINDOW_OPENGL);
  if (!window)
  {
    std::cerr << "SDL: Could not create window" << std::endl;
    return 1;
  }
  SDL_GLContext context = SDL_GL_CreateContext(window);
  if (!init_glew())
    return 1;
  init_gl();
  
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

    glFlush();
    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  
  return 0;
}
