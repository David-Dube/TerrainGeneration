#include "MiscNoise.h"
#include <cmath>

double RandomNoise::get_height(double x, double y) {
    return rand() % 255;
}