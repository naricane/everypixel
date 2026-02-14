#pragma once
#include <SFML/Graphics.hpp>

enum class PixelKind {
  Air,
  Barrier,
  Sand,
  Water,
};

struct Pixel {
  PixelKind kind = PixelKind::Air;
  bool updated = false;
};

sf::Color get_color(PixelKind kind);
unsigned int get_velocity(PixelKind kind);
