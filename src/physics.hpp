#pragma once
#include <SFML/System.hpp>

struct World;

void move_pixel(World &w, sf::Vector2i from, sf::Vector2i to);
sf::Vector2i get_next_pixel_pos(World &w, sf::Vector2i pos, int dir);

sf::Vector2i process_sand(World &w, sf::Vector2i pos, int dir);
sf::Vector2i process_water(World &w, sf::Vector2i pos, int dir);
