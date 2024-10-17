#include "Lake.h"

// TODO add oceans
double LakeBiome::get_height(double x, double y) {
    y *= 10;
    double theta = atan2(y, x) + wave_rotation;
    double distance_sq = sqrt(x * x + y * y);
    x = cos(theta) * distance_sq;
    y = sin(theta) * distance_sq;

    return noise.get_height(x, y) * 0.2;
}

void LakeBiome::handle_key(SDL_KeyboardEvent key) {

}