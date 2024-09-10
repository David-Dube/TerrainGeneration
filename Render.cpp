#include "Render.h"

#include <unordered_map>
#include <utility>
#include <string>
#include <vector>

#define CACHE_SIZE 1000

struct Tile
{
    int x, y;
    SDL_Surface *surf;
};

std::string cache_key(int x, int y) {
    return std::to_string(x) + std::to_string(y);
}

int current_index = 0;
Tile tile_cache[CACHE_SIZE];
std::unordered_map<std::string, int> tile_map;

NoiseGenerator *generator;

void render_init(NoiseGenerator *g)
{
    memset(tile_cache, 0, sizeof(Tile) * CACHE_SIZE);
    generator = g;
}

/**
 * Returns a surface with a 32x32 pixel heightmap at left, top
 */
SDL_Surface *get_chunk_surface(int left, int top)
{
    // if (tile_cache.contains(cache_key(left, top)))
    // {
    //     return tile_cache.at(cache_key(left, top)).surf;
    // }

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 32, 32, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x00000000);
    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            uint8_t height = std::clamp(generator->get_height(left + x, top + y), 0.0, 255.0);
            *((Uint32 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = height << 24;
        }
    }

    current_index = (current_index + 1) % CACHE_SIZE;
    if (tile_cache[current_index] != 0) free()
    tile_cache.emplace(cache_key(left, top), Tile{left, top, surf});

    return surf;
}

/**
 * Renders a heightmap to the surface at (left, top)
 * Width and height are rounded up to the nearest multiple of 32
 * TODO fix this ^^
 */
void render_screen(int left, int top, int width, int height, SDL_Surface *target)
{
    for (int x = left - (left % 32); x < left + width; x += 32)
    {
        for (int y = top - (top % 32); y < top + height; y++)
        {
            SDL_Surface *chunk = get_chunk_surface(x, y);
            SDL_Rect dst_rect = {x, y, 32, 32};
            SDL_BlitSurface(chunk, NULL, target, &dst_rect);
        }
    }
}