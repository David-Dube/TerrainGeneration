#include "Grasslands.h"

double GrasslandsBiome::get_height(double x, double y) {
    return (noise.get_height(x, y) / 255 * 0.3 + 0.5) * 255;
}

void GrasslandsBiome::handle_key(SDL_KeyboardEvent key) {

}