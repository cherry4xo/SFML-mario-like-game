#pragma once

#include "main.h"
#include "map.h"

#ifndef HERO_HEADER
#define HERO_HEADER

class Hero {
protected:
	std::string			image_file_path;
	sf::Image			hero_image;
	sf::Texture			hero_texture;
	sf::Sprite			hero_sprite;
	float				hero_sprite_scale;
	float				x, dx;
	float				y, dy;
	float				w, h;
	float				speed;
	int					dir;
	int					score;

public:
					Hero(std::string path, float x, float y, float w, float h);
	void			Init();
	void			Draw(sf::RenderWindow* window);
	void			set_position(float x, float y);
	void			set_texture_rect(sf::IntRect r);
	void			set_color(sf::Color color);
	void			update(float time, TMapWidget* m);
	void			set_dir(int dir), set_speed(float speed);
	float			get_x(), get_y();
	float			get_speed();
	void			interaction_with_map(TMapWidget* m);
	int				get_score();

};

#endif