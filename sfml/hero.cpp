#include "hero.h"
#include <iostream>

Hero::Hero(std::string path, float x, float y, float w, float h) :
	image_file_path(path),
	hero_image(),
	hero_texture(),
	hero_sprite(),
	x(x),
	y(x),
	w(w),
	h(h),
	dx(0),
	dy(0),
	speed(0),
	dir(0),
	score(0),
	hero_sprite_scale(4) {}

void Hero::Init() 
{
		hero_image.loadFromFile(image_file_path);
		hero_image.createMaskFromColor(sf::Color(255, 255, 255));
		hero_texture.loadFromImage(hero_image);
		hero_sprite.setTexture(hero_texture);
		hero_sprite.setTextureRect(sf::IntRect(8, 50, w, h));
		hero_sprite.setScale(hero_sprite_scale, hero_sprite_scale);
		hero_sprite.setPosition(x, y);
}

void Hero::set_position(float x, float y) { this->x = x; this->y = y; }

void Hero::Draw(sf::RenderWindow* window) { window->draw(hero_sprite); }

void Hero::set_texture_rect(sf::IntRect r) { hero_sprite.setTextureRect(r); }

void Hero::set_color(sf::Color color) { hero_sprite.setColor(color); }

void Hero::update(float time, TMapWidget* m)
{
	switch (dir) {
	case 0: dx = speed, dy = 0; break;
	case 1: dx = -speed; dy = 0; break;
	case 2: dx = 0; dy = speed; break;
	case 3: dx = 0; dy = -speed; break;
	case 4: dx = 0; dy = 0; break;
	}

	x += dx * time;
	y += dy * time;

	if (x + dx >= 1728 - 152) x = 1728 - 152;//773;
	if (x + dx < 0) x = 0;
	if (y + dy >= 960 - 168) y = 960 - 168;//573;
	if (y + dy < 0) y = 0;


	speed = 0;
	hero_sprite.setPosition(x, y);
	this->interaction_with_map(m);
}

void Hero::set_dir(int dir) { this->dir = dir; }
void Hero::set_speed(float speed) { this->speed = speed; }

float Hero::get_x() { return this->x; }
float Hero::get_y() { return this->y; }
float Hero::get_speed() { return this->speed; }

void Hero::interaction_with_map(TMapWidget* m) 
{
	for(int i = y / 64; i < (y + h * 4) / 64; ++i)
		for (int j = x / 64; j < (x + w * 4) / 64; ++j) {
			if (m->get_tile_map()[i][j] == '0' ||
				m->get_tile_map()[i][j] == '1' ||
				m->get_tile_map()[i][j] == '2' ||
				m->get_tile_map()[i][j] == '3' ||
				m->get_tile_map()[i][j] == '4' ||
				m->get_tile_map()[i][j] == '5' ||
				m->get_tile_map()[i][j] == '6' ||
				m->get_tile_map()[i][j] == '7')
			{
				if (dy > 0) { y = i * 64 - h * 4; }
				if (dy < 0) { y = i * 64 + 64; }
				if (dx > 0) { x = j * 64 - w * 4; }
				if (dx < 0) { x = j * 64 + 64; }
			}
			if (m->get_tile_map()[i][j] == '8') {
				score++;
				m->set_tile(i, j, ' ');
				std::cout << "score: " << score << "\n";
			}
		}
}

int Hero::get_score() { return this->score; }