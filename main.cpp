#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Render.h"
#include "TerrainNoise.h"
#include "MiscNoise.h"
#include "ColorMap.h"
#include "Lake.h"
#include "Grasslands.h"
#include "Mountain.h"

SDL_Window *window = NULL;
SDL_Surface *window_surf = NULL;
const Uint8* keys;
const int WIDTH = 640;
const int HEIGHT = 480;

struct {
    double pan_speed = 20;
} settings;
NoiseGenerator *noise;

void initialize() {
    // Initialize SDL systems
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n",
               SDL_GetError());
    }
    else
    {
        // Create a window
        window = SDL_CreateWindow("Terrain Generation",
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

    TTF_Init();
    IMG_Init(0);

    keys = SDL_GetKeyboardState(NULL);

    noise = new TerrainNoise();
    render_init(noise);
}

int main(int argc, char *args[])
{
    double viewport_top = 0;
    double viewport_left = 0;
    double viewport_scale = 1;

    initialize();

    // Poll for events and wait till user closes window
    bool quit = false;
    SDL_Event currentEvent;
    Uint64 start_timestamp;
    while (!quit)
    {
        start_timestamp = SDL_GetTicks64();
        SDL_PumpEvents();
        while (SDL_PollEvent(&currentEvent) != 0)
        {
            switch (currentEvent.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    noise->handle_key(currentEvent.key);
                    if (currentEvent.key.keysym.scancode == SDL_SCANCODE_S) export_range(viewport_left, viewport_top, WIDTH / viewport_scale, HEIGHT / viewport_scale, viewport_scale);
                    if (!(currentEvent.key.keysym.scancode == SDL_SCANCODE_LEFT || currentEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT || currentEvent.key.keysym.scancode == SDL_SCANCODE_UP || currentEvent.key.keysym.scancode == SDL_SCANCODE_DOWN || currentEvent.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET || currentEvent.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)) {
                        drop_cache();
                    }
                    break;

            }
        }

        if (keys[SDL_SCANCODE_RIGHT]) viewport_left += settings.pan_speed / viewport_scale;
        if (keys[SDL_SCANCODE_LEFT]) viewport_left -= settings.pan_speed / viewport_scale;
        if (keys[SDL_SCANCODE_UP]) viewport_top -= settings.pan_speed / viewport_scale;
        if (keys[SDL_SCANCODE_DOWN]) viewport_top += settings.pan_speed / viewport_scale;

        if (keys[SDL_SCANCODE_RIGHTBRACKET]) viewport_scale *= 1.01;
        if (keys[SDL_SCANCODE_LEFTBRACKET]) viewport_scale *= 0.99;

        if (keys[SDL_SCANCODE_BACKSLASH]) viewport_scale = 1;

        SDL_FillRect(window_surf, NULL, 0x0);
        render_screen(viewport_left, viewport_top, WIDTH / viewport_scale, HEIGHT / viewport_scale, viewport_scale, window_surf);
        SDL_UpdateWindowSurface(window);

        Uint32 dt = SDL_GetTicks() - start_timestamp;
        double real_fps;
        if (dt < 16) {
            SDL_Delay((Uint32) 16 - dt);
            real_fps = 60.0;
        } else {
            real_fps = 1000.0 / dt;
        }
        display_fps = (display_fps * 9 + real_fps) / 10.0;
    }

    // Free up window
    SDL_DestroyWindow(window);
    // Shutdown SDL
    SDL_Quit();

    return 0;
}