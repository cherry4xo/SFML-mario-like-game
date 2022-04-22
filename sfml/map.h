#pragma once
#include "main.h"
#include <vector>
#ifndef MAP_HEADER
#define MAP_HEADER

class TMapWidget {
protected:
	int								x;
	int								y;
	int								width;
	int								height;
	sf::Image						map_image;
	sf::Texture						map_texture;
	sf::Sprite						map_sprite;
	std::vector<sf::String>			tile_map;

public:
									TMapWidget(int x, int y, int width, int height);
									~TMapWidget();
	void							Draw(sf::RenderWindow* window);
	std::vector<sf::String>			get_tile_map();
	void							set_tile(int i, int j, char ch);
};


#endif