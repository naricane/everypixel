#include "factory.hpp"

Pixel create_air() { return {PixelKind::Air, false}; }
Pixel create_water() { return {PixelKind::Water, false}; }
Pixel create_sand() { return {PixelKind::Sand, false}; }
