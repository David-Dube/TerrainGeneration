#include "TerrainNoise.h"
#include "Perlin.h"
#include <cmath>

int layer = 0;

double TerrainNoise::get_height(double x, double y) {
    double biome = biome_generator.get_height(x / 10, y / 10) / 255;
    switch (layer) {
        case 0:
            // return asin(biome_generator.get_height(x / 10, y / 10) / 255.0) * 255.0;
            if (biome < 0.33) {
                return biomes[0]->get_height(x, y);
            } else {
                return ((biome - 0.33) / 0.67) * biomes[2]->get_height(x, y) + (1-((biome - 0.33) / 0.67)) * biomes[1]->get_height(x, y);
            }
            return 255;
            break;
        case 1:
            if (biome < 0.33) return 0;
            return biome * 255;
            break;
    }
    return 0;
}

void TerrainNoise::handle_key(SDL_KeyboardEvent key) {
    switch (key.keysym.scancode) {
        case SDL_SCANCODE_EQUALS:
            base_generator.z = base_generator.z + 0.01;
            break;
        case SDL_SCANCODE_0:
            layer = 0;
            break;
        case SDL_SCANCODE_1:
            layer = 1;
            break;
    }
}