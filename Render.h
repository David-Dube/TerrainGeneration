#pragma once

#include <SDL2/SDL2.h>
#include "Noise.h"
#include <algorithm>

extern double display_fps;

void render_init(NoiseGenerator* generator);

SDL_Surface* get_chunk_surface(int left, int top);

void render_screen(int left, int top, int width, int height, double scale, SDL_Surface* target);