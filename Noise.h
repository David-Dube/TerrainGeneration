#pragma once
#include <SDL2/SDL_events.h>
#include "ColorMap.h"

class NoiseGenerator {
public:
    NoiseGenerator() {}
    ~NoiseGenerator() {}

    virtual double get_height(double x, double y) = 0;
    virtual Color get_color(double x, double y) {
        return ramp_1d(get_height(x, y)/255, {0, 0, 0}, {255, 255, 255});
    }

    virtual void handle_key(SDL_KeyboardEvent key) {
        printf("default virtual\n");
    }
};