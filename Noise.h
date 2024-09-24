#pragma once
#include <SDL2/SDL_events.h>

class NoiseGenerator {
public:
    NoiseGenerator() {}

    virtual double get_height(double x, double y) = 0;

    virtual void handle_key(SDL_KeyboardEvent key) {
        printf("default virtual\n");
    }
};