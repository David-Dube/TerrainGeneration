#include "Perlin.h"

PerlinNoise::PerlinNoise(int octaves) {
    this->octaves = octaves;
    perlin.reseed(rand());
}

double PerlinNoise::get_height(double x, double y) {
    return perlin.octave3D_01(x * 0.01, y * 0.01, this->z, octaves) * 255;
}