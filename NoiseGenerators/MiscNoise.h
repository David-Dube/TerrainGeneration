#pragma once

#include "Noise.h"

class RandomNoise : public NoiseGenerator {
public:
    double get_height(double x, double y);
};