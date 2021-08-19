#include "sdl.h"
#include "gfx.h"

#define RENDER_WIDTH  1920
#define RENDER_HEIGHT 1080

void randomize_buffer(char *buffer)
{
    // update pixel data & update texture
    int r = rand() % 255;
    for (int y = 0; y < RENDER_HEIGHT; ++y) {
        for (int x = 0; x < RENDER_WIDTH; ++x) {
            buffer[(y * RENDER_WIDTH * 3) + x*3 + 0] = x / r; // r
            buffer[(y * RENDER_WIDTH * 3) + x*3 + 1] = y % r; // g
            buffer[(y * RENDER_WIDTH * 3) + x*3 + 2] = x % r; // b
        }
    }
}

int last_time;
int main()
{
    srand(time(0));

    SDL_Window *window = pixel_sdl_new_window("Test", RENDER_WIDTH, RENDER_HEIGHT, 0);
    const char *buffer = pixel_gfx_init(RENDER_WIDTH, RENDER_HEIGHT, GL_RGB);

    int Running = 1;
    while (Running) {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                    default:
                        break;
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }

        randomize_buffer(buffer);

        // display FPS
        int current_time = SDL_GetTicks();
        double fps = 1000 / (current_time - last_time);
        char title[100];
        sprintf(title, "Opengl SDL Demo (FPS: %f)", fps);
        SDL_SetWindowTitle(window, title);
        last_time = current_time;

        pixel_gfx_update(buffer, 255, 0, 0, 255);
        pixel_sdl_render(window);
    }

    pixel_gfx_end(buffer);
    pixel_sdl_end(window);
}

