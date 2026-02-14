#include "pixel.hpp"

sf::Color get_color(PixelKind kind) {
  switch (kind) {
  case PixelKind::Sand:
    return sf::Color::Yellow;
  case PixelKind::Water:
    return sf::Color::Blue;
  default:
    return sf::Color::Black;
  }
}

unsigned int get_velocity(PixelKind kind) {
  switch (kind) {
  case PixelKind::Sand:
    return 8;
  case PixelKind::Water:
    return 32;
  default:
    return 1;
  }
}
