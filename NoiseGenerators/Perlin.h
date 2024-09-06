#pragma once

#include "Noise.h"

class PerlinNoise : public NoiseGenerator {
    double get_height(double x, double y);
};