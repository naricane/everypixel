#include "world.hpp"
#include "physics.hpp"
#include "src/pixel.hpp"

World::World() { img.resize({WIDTH, HEIGHT}); }

void World::simulate() {
  for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
    pixels[i].updated = false;
  }

  bool left_to_right = (rand() % 2 == 0);
  for (int y = HEIGHT - 1; y >= 0; y--) {
    for (int x = 0; x < static_cast<int>(WIDTH); x++) {
      int physics_x = left_to_right ? x : (WIDTH - 1 - x);

      Pixel px = at({physics_x, y});
      if (px.kind == PixelKind::Air || px.updated) {
        continue;
      }

      sf::Vector2i pos = {physics_x, y};
      int dir = (rand() % 2 == 0) ? 1 : -1;

      for (unsigned int i = 0; i < get_velocity(px.kind); i++) {
        sf::Vector2i next_pos = get_next_pixel_pos(*this, pos, dir);

        if (next_pos != pos) {
          move_pixel(*this, pos, next_pos);
          pos = next_pos;
        } else {
          break;
        }
      }

      at(pos).updated = true;
    }
  }

  for (unsigned int y = 0; y < HEIGHT; y++) {
    for (unsigned int x = 0; x < WIDTH; x++) {
      img.setPixel(
          {x, y},
          get_color(at({static_cast<int>(x), static_cast<int>(y)}).kind));
    }
  }
}

PixelKind World::kind_at(sf::Vector2i pos) {
  if (pos.x >= 0 && pos.x < static_cast<int>(WIDTH) && pos.y >= 0 &&
      pos.y < static_cast<int>(HEIGHT)) {
    return pixels[pos.x + pos.y * WIDTH].kind;
  } else {
    return PixelKind::Barrier;
  }
}

Pixel &World::at(sf::Vector2i pos) { return pixels[pos.x + pos.y * WIDTH]; }
