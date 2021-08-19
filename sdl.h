#ifndef PIXEL_SDL_H
#define PIXEL_SDL_H

#include "SDL2/SDL.h"

// wrapper around SDL_CreateWindow (appends SDL_WINDOW_OPENGL to flags)
SDL_Window *pixel_sdl_new_window(const char *title, int width, int height, unsigned long flags);

// update SDL from OpenGL
void pixel_sdl_render(SDL_Window *window);

// end SDL and cleanup
void pixel_sdl_end(SDL_Window *window);

#endif
