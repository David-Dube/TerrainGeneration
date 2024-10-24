#pragma once

#include "Noise.h"

class RandomNoise : public NoiseGenerator
{
public:
    double get_height(double x, double y);
};

class CircleNoise : public NoiseGenerator
{
public:
    double get_height(double x, double y);
};

class CircleFalloffNoise : public NoiseGenerator
{
public:
    double get_height(double x, double y);
};

class TestNoise : public NoiseGenerator {
    public:
    double get_height(double x, double y);
};