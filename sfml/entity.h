#pragma once

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "view.h"
#include "level.h"
#include <list>

class Entity 
{
protected:
	std::vector <Object> obj;
	float x, dx;
	float y, dy;
	float speed, move_timer;
	int w, h;
	bool is_move, on_ground;
	sf::Texture texture;
public:
	bool life;
	int health;
	sf::String name;
	std::pair<float, float> get_d();
	std::pair<float, float> get_coords();
	bool get_on_ground();
	void set_d(float dx, float dy);
	void set_x(float x);
	void set_y(float y);
	void change_health(int h);
	Entity(sf::Image& image, sf::String name, float x, float y, int w, int h);
	sf::FloatRect get_rect();
	void Draw(sf::RenderWindow* window);
	sf::Sprite sprite;
	virtual void update(float time, Hero_view* view, float& current_frame) = 0;
};


class Player : public Entity
{
protected:
	enum { left, right, up, down, jump, stay } state;
	int score;

public:
	bool win;
	Player(sf::Image& image, sf::String name, TileMap& lev, float x, float y, int w, int h);
	void control(float& current_frame, float time);
	void check_collision_with_map(float dx, float dy);
	void update(float time, Hero_view* view, float& current_frame);
};


class Enemy : public Entity
{
public:
	Enemy(sf::Image& image, sf::String name, TileMap& lev, float x, float y, int w, int h);
	void check_collision_with_map(float dx, float dy);
	void update(float time, Hero_view* view, float& current_frame);
};

#endif