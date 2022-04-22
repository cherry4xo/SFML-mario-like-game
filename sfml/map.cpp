#include "map.h"

TMapWidget::TMapWidget(int x, int y, int width, int height) : 
	x(x), 
	y(y), 
	width(width), 
	height(height),
	map_image(),
	map_texture(),
	map_sprite()
{
	map_image.loadFromFile("source/map_tileset.png");
	map_image.createMaskFromColor(sf::Color(255, 255, 255));
	map_texture.loadFromImage(map_image);
	map_sprite.setTexture(map_texture);
	tile_map = {
	"100000000000000000000000002",
	"5      8      8      8    7",
	"5   8                     7",
	"5       8      8          7",
	"5                    8    7",
	"5   8       88            7",
	"5               88        7",
	"58      8     8       8   7",
	"5                8        7",
	"5        8                7",
	"5   8         8    8      7",
	"5                   8     7",
	"5       8       8         7",
	"5   8       8        8    7",
	"466666666666666666666666663",
	};
}

TMapWidget::~TMapWidget() {}

void TMapWidget::Draw(sf::RenderWindow* window) 
{
	for(int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (tile_map[i][j] == '1') map_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
			if (tile_map[i][j] == '0') map_sprite.setTextureRect(sf::IntRect(65, 0, 64, 64));
			if (tile_map[i][j] == '2') map_sprite.setTextureRect(sf::IntRect(129, 0, 64, 64));
			if (tile_map[i][j] == '3') map_sprite.setTextureRect(sf::IntRect(129, 129, 64, 64));
			if (tile_map[i][j] == '4') map_sprite.setTextureRect(sf::IntRect(0, 129, 64, 64));
			if (tile_map[i][j] == '5') map_sprite.setTextureRect(sf::IntRect(0, 65, 64, 64));
			if (tile_map[i][j] == '6') map_sprite.setTextureRect(sf::IntRect(65, 129, 64, 64));
			if (tile_map[i][j] == '7') map_sprite.setTextureRect(sf::IntRect(129, 65, 64, 64));
			if (tile_map[i][j] == ' ') map_sprite.setTextureRect(sf::IntRect(65, 65, 64, 64));
			if (tile_map[i][j] == '8') map_sprite.setTextureRect(sf::IntRect(65, 65, 64, 64));

			map_sprite.setPosition(j * 64, i * 64);
			window->draw(map_sprite);
		}

	for(int i = 0; i < MAP_HEIGHT; ++i)
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (tile_map[i][j] == '8') {
				map_sprite.setTextureRect(sf::IntRect(256, 192, 64, 64));
				map_sprite.setPosition(j * 64, i * 64);
				window->draw(map_sprite);
			}
		}
}

std::vector<sf::String> TMapWidget::get_tile_map() { return this->tile_map; }

void TMapWidget::set_tile(int i, int j, char ch) { this->tile_map[i][j] = ch; }