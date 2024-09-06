#include "Sine.h"
#include <cmath>

double SinusoidalNoise::get_height(double x, double y) {
    return sin(x / 5) * 64 + sin(y / 10) * 64 + 128;
}