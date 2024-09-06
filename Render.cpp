#include "Render.h"

NoiseGenerator* generator;

void set_generator(NoiseGenerator* g) {
    generator = g;
}

/**
 * Returns a surface with a 32x32 pixel heightmap at left, top
 */
SDL_Surface* get_chunk_surface(int left, int top) {
    SDL_Surface *surf = SDL_CreateRGBSurface(0, 32, 32, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x00000000);
    for (int x = 0; x < 32; x++) {
        for (int y = 0; y < 32; y++) {
            uint8_t height = std::clamp(generator->get_height(left + x, top + y), 0.0, 255.0);
            *((Uint32*) ((Uint8*) surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = height << 24;
        }
    }

    return surf;
}

/**
 * Renders a heightmap to the surface at (left, top)
 * Width and height are rounded up to the nearest multiple of 32
 * TODO fix this ^^
 */
void render_screen(int left, int top, int width, int height, SDL_Surface* target) {
    for (int x = left; x < left + width; x += 32) {
        for (int y = top; y < top + height; y++) {
            SDL_Surface* chunk = get_chunk_surface(x, y);
            SDL_Rect dst_rect = {x, y, 32, 32};
            SDL_BlitSurface(chunk, NULL, target, &dst_rect);
        }
    }
}