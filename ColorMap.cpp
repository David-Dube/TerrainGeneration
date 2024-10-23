#include <vector>
#include <exception>
#include <stdexcept>
#include "ColorMap.h"

Color ramp_1d(double x, Color p1, Color p2)
{
    Color result;
    result.r = p1.r + (p2.r - p1.r) * x;
    result.g = p1.g + (p2.g - p1.g) * x;
    result.b = p1.b + (p2.b - p1.b) * x;

    return result;
}

Color ramp_1d(double x, std::vector<ColorStop> &stops)
{
    if (x <= stops[0].x)
        return stops[0].c;
    if (x >= stops.back().x)
        return stops.back().c;

    for (int i = 0; i < stops.size(); i++)
    {
        if (x < stops[i].x)
        {
            return ramp_1d((x - stops[i - 1].x) / (stops[i].x - stops[i-1].x), stops[i - 1].c, stops[i].c);
        }
    }

    throw std::runtime_error("Something went wrong in ramp_1d(double, std::vector<ColorStop>)");
}

Color ramp_sigmoid(double x, Color p1, Color p2) {
    double y = 1 / (1 + pow(2.71828182846, x));
    return ramp_1d(y, p1, p2);
}

Uint32 pack_color(Color c)
{
    return c.r << 24 | c.g << 16 | c.b << 8;
}

Color unpack_color(Uint32 c) {
    return {
        c >> 24 & 0xFF,
        c >> 16 & 0xFF,
        c >> 8 & 0xFF
    };
}