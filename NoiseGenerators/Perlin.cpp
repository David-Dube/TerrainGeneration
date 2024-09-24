#include "Perlin.h"
#include "../PerlinNoise.hpp"

siv::PerlinNoise perlin;

double PerlinNoise::get_height(double x, double y) {
    return perlin.octave3D_01(x * 0.01, y * 0.01, this->z, octaves) * 255;
}