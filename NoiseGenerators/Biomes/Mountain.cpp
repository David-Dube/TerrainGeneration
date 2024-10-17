#include "Mountain.h"

double MountainBiome::get_height(double x, double y) {
    return (sqrt(noise.get_height(x, y) / 255) * 0.5 + 0.55) * 255;
}

void MountainBiome::handle_key(SDL_KeyboardEvent key) {

}