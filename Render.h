#pragma once

#include <SDL2/SDL2.h>
#include "Noise.h"
#include <algorithm>

void set_generator(NoiseGenerator* generator);

SDL_Surface* get_chunk_surface(int left, int top);

void render_screen(int left, int top, int width, int height, SDL_Surface* target);