#pragma once
#include "Noise.h"
#include "Perlin.h"

class LakeBiome : public NoiseGenerator
{
    PerlinNoise noise = PerlinNoise(1);
    double wave_rotation = 30;

public:
    LakeBiome() {}

    double get_height(double x, double y);
    void handle_key(SDL_KeyboardEvent key) override;
};