#pragma once

#include <SDL2/SDL2.h>
#include "Noise.h"
#include <algorithm>
#include <vector>
#include "ColorMap.h"

extern double display_fps;

void render_init(NoiseGenerator* generator);
void render_quit();

SDL_Surface* get_chunk_surface(int left, int top, std::vector<ColorStop> stops);
SDL_Surface* get_chunk_surface(int left, int top);

void drop_cache();

void render_screen(int left, int top, int width, int height, double scale, SDL_Surface* target, bool debug = true);

void export_range(int left, int top, int width, int height, double scale);