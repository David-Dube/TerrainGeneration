#include "Perlin.h"

double PerlinNoise::get_height(double x, double y) {
    return (x + y) * 8;
}