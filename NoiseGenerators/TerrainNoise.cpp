#include "TerrainNoise.h"
#include "Perlin.h"
#include "ColorMap.h"
#include "SDL2/SDL_image.h"
#include <cmath>
#include <unordered_map>
#include "MiscNoise.h"

int layer = 0;

SDL_Surface *biome_map;
std::unordered_map<uint32_t, std::shared_ptr<NoiseGenerator>> generator_map;

TerrainNoise::TerrainNoise() {
    biomes.push_back(std::make_shared<LakeBiome>());
    biomes.push_back(std::make_shared<GrasslandsBiome>());
    biomes.push_back(std::make_shared<MountainBiome>());

    biome_map = IMG_Load("biomes.png");
    if (biome_map == nullptr) {
        printf("Error loading biome map: %s\n", SDL_GetError());
    }

    biome_map = SDL_ConvertSurfaceFormat(biome_map, SDL_PIXELFORMAT_RGBA8888, 0);
    if (biome_map == nullptr) {
        printf("Error converting biome map: %s\n", SDL_GetError());
    }

    generator_map.emplace(0x8000FF, std::make_shared<RandomNoise>());
}

double TerrainNoise::get_height(double x, double y) {
    double biome = biome_generator.get_height(x / 10, y / 10) / 255;
    double humidity = humidity_generator.get_height(x / 10, y / 10);
    double temperature = humidity_generator.get_height(x / 10, y / 10);

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

std::vector<uint32_t> unique_colors;

Color TerrainNoise::get_color(double x, double y) {
    double humidity = humidity_generator.get_height(x / 10, y / 10);
    double temperature = temperature_generator.get_height(x / 10, y / 10);
    double bx = std::clamp(humidity, 0.0, 254.0);
    double by = std::clamp(256 - temperature, 0.0, 254.0);
    uint32_t color = *((uint32_t*) ((uint8_t*) biome_map->pixels + ((uint32_t) by * biome_map->pitch) + (uint32_t) bx * biome_map->format->BytesPerPixel));
    switch (layer) {
        case 0:
            if (generator_map.contains(color)) {
                return {(int) generator_map.at(color)->get_height(x, y), 0, 0};
            } else {
                return {0, 255, 0};
            }
            break;
        case 1:
            return unpack_color(color);
            break;
    }
    return {0, 0, 255};
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