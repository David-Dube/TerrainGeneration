#pragma once
#include <SDL2/SDL_stdinc.h>
#include <vector>

struct Color {
    int r, g, b;
};

struct ColorStop {
    double x;
    Color c;
};

/**
 * Color ramp between 2 points
 */
Color ramp_1d(double x, Color p1, Color p2);

/**
 * Color ramp between many colors
 */
Color ramp_1d(double x, std::vector<ColorStop> &stops);

Color ramp_sigmoid(double x, Color p1, Color p2);

Uint32 pack_color(Color c);
Color unpack_color(Uint32 c);