#pragma once
#include "Noise.h"
#include "Perlin.h"
#include "Lake.h"
#include "Grasslands.h"
#include "Mountain.h"
#include <vector>
#include <memory>

class TerrainNoise : public NoiseGenerator
{
    PerlinNoise base_generator = PerlinNoise(2);
    PerlinNoise biome_generator = PerlinNoise(1);
    PerlinNoise humidity_generator = PerlinNoise(1);
    PerlinNoise temperature_generator = PerlinNoise(1);

    std::vector<std::shared_ptr<NoiseGenerator>> biomes;

public:
    TerrainNoise();

    double get_height(double x, double y);
    Color get_color(double x, double y);
    void handle_key(SDL_KeyboardEvent key) override;
};
