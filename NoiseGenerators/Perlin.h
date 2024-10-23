#pragma once

#include "Noise.h"
#include "../PerlinNoise.hpp"

class PerlinNoise : public NoiseGenerator
{
    siv::PerlinNoise perlin;

public:
    int octaves;
    double z = 0;

    PerlinNoise(int octaves);

    double get_height(double x, double y);
};