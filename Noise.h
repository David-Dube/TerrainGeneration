#pragma once

class NoiseGenerator {
public:
    NoiseGenerator() {}

    virtual double get_height(double x, double y) = 0;
};