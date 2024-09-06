#include "Noise.h"

class SinusoidalNoise : public NoiseGenerator {
public:
    double get_height(double x, double y);
};