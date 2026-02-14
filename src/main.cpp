#include "factory.hpp"
#include "world.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::View get_letterbox_view(sf::View view, int w_width, int w_height) {
  float window_ratio = w_width / (float)w_height;
  float view_ratio = view.getSize().x / (float)view.getSize().y;
  float size_x = 1;
  float size_y = 1;
  float pos_x = 0;
  float pos_y = 0;

  bool horizontal_spacing = true;

  if (window_ratio < view_ratio)
    horizontal_spacing = false;

  if (horizontal_spacing) {
    size_x = view_ratio / window_ratio;
    pos_x = (1 - size_x) / 2.f;
  } else {
    size_y = window_ratio / view_ratio;
    pos_y = (1 - size_y) / 2.f;
  }

  view.setViewport(sf::FloatRect({pos_x, pos_y}, {size_x, size_y}));

  return view;
}

int main() {
  sf::RenderWindow window;
  window.create(sf::VideoMode({WIDTH, HEIGHT}), "pixels");
  window.setFramerateLimit(60);

  sf::View view;
  view.setSize({WIDTH, HEIGHT});
  view.setCenter({WIDTH / 2.f, HEIGHT / 2.f});

  sf::Clock clock;

  static World world;
  sf::Texture texture;
  if (!texture.resize({WIDTH, HEIGHT})) {
    std::cerr << "Error! Cannot create SFML texture.\n";
    return 1;
  }

  Pixel spawn_pixel = create_air();

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      } else if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        view = get_letterbox_view(view, resized->size.x, resized->size.y);
      }
    }

    sf::Vector2i m_pixel_pos = sf::Mouse::getPosition(window);
    sf::Vector2f m_world_pos = window.mapPixelToCoords(m_pixel_pos);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
      spawn_pixel = create_air();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
      spawn_pixel = create_sand();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
      spawn_pixel = create_water();
    }
    int spawn_size = 5;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      for (int i = -spawn_size; i < spawn_size; i++) {
        for (int j = -spawn_size; j < spawn_size; j++) {
          int nx = m_world_pos.x + i;
          int ny = m_world_pos.y + j;
          if (nx >= 0 && nx < static_cast<int>(WIDTH) && ny >= 0 &&
              ny < static_cast<int>(HEIGHT)) {
            world.at({nx, ny}) = spawn_pixel;
          }
        }
      }
    }

    world.simulate();
    texture.update(world.img);

    window.clear();
    window.setView(view);
    sf::Sprite sprite(texture);
    window.draw(sprite);
    window.display();
  }

  return 0;
}
