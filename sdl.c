#include "sdl.h"

#include <assert.h>
#include "SDL2/SDL_opengl.h"

SDL_GLContext pixel_sdl_glcontext;

SDL_Window *pixel_sdl_new_window(const char *title, int width, int height, unsigned long flags)
{
    SDL_Window *window = SDL_CreateWindow(title, 0, 0, width, height, flags | SDL_WINDOW_OPENGL);
    pixel_sdl_glcontext = SDL_GL_CreateContext(window);

    return window;
}

void pixel_sdl_render(SDL_Window *window)
{
    SDL_GL_SwapWindow(window);
}

void pixel_sdl_end(SDL_Window *window)
{
    SDL_GL_DeleteContext(pixel_sdl_glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
