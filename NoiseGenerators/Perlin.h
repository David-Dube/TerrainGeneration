#pragma once

#include "Noise.h"

class PerlinNoise : public NoiseGenerator
{
public:
    int octaves;
    double z = 0;

    PerlinNoise(int octaves)
    {
        this->octaves = octaves;
    }

    double get_height(double x, double y);
};