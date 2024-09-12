#include "Render.h"

#include <unordered_map>
#include <utility>
#include <string>
#include <vector>
#include <cmath>

#define CACHE_SIZE 5000

struct Tile
{
    int x, y;
    SDL_Surface *surf;
};

std::string cache_key(int x, int y) {
    return std::to_string(x) + "," + std::to_string(y);
}

int current_index = 0;
Tile tile_cache[CACHE_SIZE];
std::unordered_map<std::string, int> tile_map;

NoiseGenerator *generator;

void render_init(NoiseGenerator *g)
{
    printf("tile: %d\n", sizeof(Tile));
    memset(tile_cache, 0, sizeof(Tile) * CACHE_SIZE);
    generator = g;
}

/**
 * Returns a surface with a 32x32 pixel heightmap at left, top
 */
SDL_Surface *get_chunk_surface(int left, int top)
{
    if (tile_map.contains(cache_key(left, top)))
    {
        return tile_cache[tile_map.at(cache_key(left, top))].surf;
    }

    SDL_Surface *surf = SDL_CreateRGBSurface(0, 32, 32, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x00000000);
    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 32; y++)
        {
            uint8_t height = std::clamp(generator->get_height(left + x, top + y), 0.0, 255.0);            
            *((Uint32 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = height << 24;
            // if (x == 0 || x == 31 || y == 0 || y == 31) *((Uint32 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = 0x00FF0000;
        }
    }

    current_index = (current_index + 1) % CACHE_SIZE;
    SDL_FreeSurface(tile_cache[current_index].surf);
    tile_map.erase(cache_key(tile_cache[current_index].x, tile_cache[current_index].y));
    tile_cache[current_index] = Tile{left, top, surf};
    tile_map.emplace(cache_key(left, top), current_index);

    return surf;
}

// https://stackoverflow.com/questions/3407012/rounding-up-to-the-nearest-multiple-of-a-number
// multiple must be a power of 2
int roundUp(int numToRound, int multiple) 
{
    return (numToRound + multiple - 1) & -multiple;
}


/**
 * Renders a portion of a heightmap (left, top, left+width, top+height) to the surface at (0,0)
 */
void render_screen(int left, int top, int width, int height, double scale, SDL_Surface *target)
{
    int true_left = roundUp(left, 32) - 32;
    int true_top = roundUp(top, 32) - 32;
    for (int x = true_left; x < left + width; x += 32)
    {
        for (int y = true_top; y < top + height; y += 32)
        {
            SDL_Surface *chunk = get_chunk_surface(x, y);
            SDL_Rect dst_rect = {round((x - left) * scale), round((y - top) * scale), round(32 * scale), round(32 * scale)};
            SDL_BlitScaled(chunk, NULL, target, &dst_rect);
        }
    }
}