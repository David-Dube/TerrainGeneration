#pragma once
#include "Noise.h"
#include "Perlin.h"

class GrasslandsBiome : public NoiseGenerator
{
    PerlinNoise noise = PerlinNoise(1);

public:
    GrasslandsBiome() {}

    double get_height(double x, double y);
    void handle_key(SDL_KeyboardEvent key) override;
};