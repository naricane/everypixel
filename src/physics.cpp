#include "physics.hpp"
#include "world.hpp"
#include <algorithm>

void move_pixel(World &w, sf::Vector2i from, sf::Vector2i to) {
  std::swap(w.at(from), w.at(to));
}

sf::Vector2i get_next_pixel_pos(World &w, sf::Vector2i pos, int dir) {
  Pixel &px = w.at(pos);
  switch (px.kind) {
  case PixelKind::Sand:
    return process_sand(w, pos, dir);
  case PixelKind::Water:
    return process_water(w, pos, dir);
  default:
    return pos;
  }
}

static bool is_empty(World &w, sf::Vector2i pos) {
  return w.kind_at(pos) == PixelKind::Air;
}

static bool is_fluid(World &w, sf::Vector2i pos) {
  return w.kind_at(pos) == PixelKind::Water;
}

static bool is_empty_or_fluid(World &w, sf::Vector2i pos) {
  return is_empty(w, pos) || is_fluid(w, pos);
}

sf::Vector2i process_sand(World &w, sf::Vector2i pos, int dir) {
  if (is_empty(w, {pos.x, pos.y + 1})) {
    return {pos.x, pos.y + 1};
  }

  if (is_fluid(w, {pos.x, pos.y + 1})) {
    if (is_empty(w, {pos.x - dir, pos.y + 1})) {
      return {pos.x - dir, pos.y + 1};
    }
    if (is_empty(w, {pos.x + dir, pos.y + 1})) {
      return {pos.x + dir, pos.y + 1};
    }

    return {pos.x, pos.y + 1};
  }

  if (is_empty_or_fluid(w, {pos.x - dir, pos.y + 1})) {
    return {pos.x - dir, pos.y + 1};
  }
  if (is_empty_or_fluid(w, {pos.x + dir, pos.y + 1})) {
    return {pos.x + dir, pos.y + 1};
  }

  return pos;
}

sf::Vector2i process_water(World &w, sf::Vector2i pos, int dir) {
  if (is_empty(w, {pos.x, pos.y + 1})) {
    return {pos.x, pos.y + 1};
  }
  if (is_empty(w, {pos.x - dir, pos.y})) {
    return {pos.x - dir, pos.y};
  }
  if (is_empty(w, {pos.x + dir, pos.y})) {
    return {pos.x + dir, pos.y};
  }
  if (is_empty(w, {pos.x - dir, pos.y + 1})) {
    return {pos.x - dir, pos.y + 1};
  }
  if (is_empty(w, {pos.x + dir, pos.y + 1})) {
    return {pos.x + dir, pos.y + 1};
  }

  return pos;
}
