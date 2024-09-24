#include <unordered_map>
#include <utility>
#include <string>
#include <vector>
#include <cmath>

#include <SDL2/SDL_ttf.h>

#include "ColorMap.h"
#include "Render.h"

#define CACHE_SIZE 10000

double display_fps = 0;

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

TTF_Font *font;

int allocations = 0;

std::vector<ColorStop> color_stops;

void render_init(NoiseGenerator *g)
{
    memset(tile_cache, 0, sizeof(Tile) * CACHE_SIZE);
    generator = g;
    font = TTF_OpenFont("font.ttf", 12);

    color_stops.push_back(ColorStop{0, {0, 0, 128}}); // dark blue, deep ocean
    color_stops.push_back(ColorStop{0.2, {0, 0, 255}}); // light blue, shallow ocean
    color_stops.push_back(ColorStop{0.2, {235, 198, 52}}); // yellow, beach
    color_stops.push_back(ColorStop{0.5, {0, 200, 0}}); // light green, low grass
    color_stops.push_back(ColorStop{0.8, {0, 150, 0}}); // dark green, high grass
    color_stops.push_back(ColorStop{0.9, {128, 128, 128}}); // gray, mountain
    color_stops.push_back(ColorStop(1, {255, 255, 255})); // white, snow
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
            Color c = ramp_1d(height / 255.0, color_stops);
            *((Uint32 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = pack_color(c);

            // if (x == 0 || x == 31 || y == 0 || y == 31) *((Uint32 *)((Uint8 *)surf->pixels + y * surf->pitch + x * surf->format->BytesPerPixel)) = 0x00FF0000;
        }
    }

    current_index = (current_index + 1) % CACHE_SIZE;
    SDL_FreeSurface(tile_cache[current_index].surf);
    tile_map.erase(cache_key(tile_cache[current_index].x, tile_cache[current_index].y));
    tile_cache[current_index] = Tile{left, top, surf};
    tile_map.emplace(cache_key(left, top), current_index);
    ++allocations;
 
    return surf;
}

void drop_cache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        SDL_FreeSurface(tile_cache[i].surf);
        tile_map.erase(cache_key(tile_cache[i].x, tile_cache[i].y));
        tile_cache[i] = {0, 0, nullptr};
    }
    current_index = 0;
}

// https://stackoverflow.com/questions/3407012/rounding-up-to-the-nearest-multiple-of-a-number
// multiple must be a power of 2
int roundUp(int numToRound, int multiple) 
{
    return (numToRound + multiple - 1) & -multiple;
}

std::string get_debug_text() {
    std::string result;
    result += "Cache size: " + std::to_string(tile_map.size()) + '\n';
    result += "Allocations: " + std::to_string(allocations) + '\n';
    result += "FPS: " + std::to_string((int) display_fps) + '\n';

    return result;
}

/**
 * Renders a portion of a heightmap (left, top, left+width, top+height) to the surface at (0,0)
 */
void render_screen(int left, int top, int width, int height, double scale, SDL_Surface *target)
{
    allocations = 0;
    int true_left = roundUp(left, 32) - 32;
    int true_top = roundUp(top, 32) - 32;
    for (int x = true_left; x < left + width; x += 32)
    {
        for (int y = true_top; y < top + height; y += 32)
        {
            SDL_Surface *chunk = get_chunk_surface(x, y);
            SDL_Rect dst_rect = {(int) round((x - left) * scale), (int) round((y - top) * scale), (int) round(32 * scale), (int) round(32 * scale)};
            SDL_BlitScaled(chunk, NULL, target, &dst_rect);
        }
    }

    SDL_Surface *text_surface = TTF_RenderText_Solid_Wrapped(font, get_debug_text().c_str(), {0, 255, 0}, width);
    SDL_Rect rect = {0, 0, text_surface->w, text_surface->h};
    SDL_BlitSurface(text_surface, NULL, target, &rect);
}