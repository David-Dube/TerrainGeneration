#include "TerrainNoise.h"
#include "Perlin.h"

double TerrainNoise::get_height(double x, double y) {
    return base_generator.get_height(x, y);
}

void TerrainNoise::handle_key(SDL_KeyboardEvent key) {
    switch (key.keysym.scancode) {
        case SDL_SCANCODE_EQUALS:
            base_generator.z = base_generator.z + 0.01;
            break;
    }
}