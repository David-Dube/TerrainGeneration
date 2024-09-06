#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "Render.h"
#include "Sine.h"
#include "Perlin.h"
#include "MiscNoise.h"

SDL_Window *window = NULL;
SDL_Surface *window_surf = NULL;
const int WIDTH = 640;
const int HEIGHT = 480;
int main(int argc, char *args[])
{

    // Initialize SDL systems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else
    {
        // Create a window
        window = SDL_CreateWindow("BGFX Tutorial",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH, HEIGHT,
                                  SDL_WINDOW_SHOWN);
        window_surf = SDL_GetWindowSurface(window);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n",
                   SDL_GetError());
        }
    }

    NoiseGenerator* noise = new RandomNoise();
    set_generator(noise);

    render_screen(0, 0, WIDTH, HEIGHT, window_surf);

    SDL_UpdateWindowSurface(window);

    // Poll for events and wait till user closes window
    bool quit = false;
    SDL_Event currentEvent;
    while (!quit)
    {
        while (SDL_PollEvent(&currentEvent) != 0)
        {
            if (currentEvent.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Free up window
    SDL_DestroyWindow(window);
    // Shutdown SDL
    SDL_Quit();

    return 0;
}