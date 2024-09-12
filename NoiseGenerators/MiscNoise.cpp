#include "MiscNoise.h"
#include <cmath>


double RandomNoise::get_height(double x, double y) {
    srand(x + y);
    return rand() % 255;
}

double CircleNoise::get_height(double x, double y) {
    return 255 - ((x * x + y * y) / 1000);
    if (x * x + y * y < 1000) return 255;
    return 0;
}