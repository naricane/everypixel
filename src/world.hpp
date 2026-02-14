#pragma once
#include "pixel.hpp"
#include <SFML/Graphics.hpp>

constexpr uint32_t WIDTH = 320 * 2;
constexpr uint32_t HEIGHT = 180 * 2;

struct World {
  Pixel pixels[WIDTH * HEIGHT];

  sf::Image img;
  sf::Texture texture;

  World();
  void simulate();
  PixelKind kind_at(sf::Vector2i pos);
  Pixel &at(sf::Vector2i pos);
};
