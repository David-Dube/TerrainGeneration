#include "TerrainNoise.h"
#include "Perlin.h"
#include <cmath>

double TerrainNoise::get_height(double x, double y) {
    return asin(base_generator.get_height(x, y) / 255.0) * 255.0;
}

void TerrainNoise::handle_key(SDL_KeyboardEvent key) {
    switch (key.keysym.scancode) {
        case SDL_SCANCODE_EQUALS:
            base_generator.z = base_generator.z + 0.01;
            break;
    }
}