#pragma once
#include "Noise.h"
#include "Perlin.h"

class MountainBiome : public NoiseGenerator
{
    PerlinNoise noise = PerlinNoise(1);

public:
    MountainBiome() {}

    double get_height(double x, double y);
    void handle_key(SDL_KeyboardEvent key) override;
};