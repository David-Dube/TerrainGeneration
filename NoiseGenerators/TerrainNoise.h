#pragma once
#include "Noise.h"
#include "Perlin.h"

class TerrainNoise : public NoiseGenerator
{
    PerlinNoise base_generator = PerlinNoise(2);

public:
    double get_height(double x, double y);
    void handle_key(SDL_KeyboardEvent key) override;
};
