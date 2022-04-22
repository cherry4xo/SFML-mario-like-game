#include "entity.h"

Entity::Entity(sf::Image& image, sf::String name, float x, float y, int w, int h) :
	name(name),
	x(x), y(y),
	w(w), h(h),
	move_timer(0),
	speed(0),
	health(100),
	dx(0), dy(0), 
	life(true), on_ground(false), is_move(false)
{
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setOrigin(w / 2, h / 2);
}

sf::FloatRect Entity::get_rect()
{
	return sf::FloatRect(x, y, w, h);
}

void Entity::Draw(sf::RenderWindow* window) { window->draw(this->sprite); }

std::pair<float, float> Entity::get_d() { return std::make_pair(this->dx, this->dy); }
bool Entity::get_on_ground() { return this->on_ground; }
std::pair<float, float> Entity::get_coords() { return std::make_pair(x, y); }

void Entity::set_d(float dx, float dy) { this->dx = dx; this->dy = dy; }
void Entity::set_x(float x) { this->x = x; }
void Entity::set_y(float y) { this->y = y; }
void Entity::change_health(int h) { this->health += h; }

Player::Player(sf::Image& image, sf::String name, TileMap& lev, float x, float y, int w, int h) :
	Entity(image, name, x, y, w, h),
	score(0), state(stay), win(false)
{
	obj = lev.getAllObjects();
	if (name == "Player1") sprite.setTextureRect(sf::IntRect(204, 0, 17, 16));
}

void Player::control(float& current_frame, float time)
{
	if (sf::Keyboard::isKeyPressed) 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			state = left; speed = -(0.2);
			current_frame += 0.01 * time;
			if (current_frame > 6) current_frame -= 6;
			sprite.setTextureRect(sf::IntRect(180 - 30 * int(current_frame), 0, 17, 16));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
			state = right; speed = 0.2;
			current_frame += 0.01 * time;
			if (current_frame > 6) current_frame -= 6;
			sprite.setTextureRect(sf::IntRect(210 + 30 * int(current_frame), 0, 17, 16));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (on_ground)) { state = jump; dy = -(0.5); on_ground = false; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { state = down; }
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { speed = 0.5; }
		else speed = 0.2;*/
	}
}

void Player::check_collision_with_map(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); ++i) {
		if (get_rect().intersects(obj[i].rect)) {
			if (obj[i].name == "solid" || obj[i].name == "lucky" || obj[i].name == "tube") {
				if (Dy > 0) { y = obj[i].rect.top - h; dy = 0.5; on_ground = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; dx = 0; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0; }
			}
			if (obj[i].name == "end") win = true;
			if (obj[i].name == "die") life = false;
		}
		else if (Dy <= 0) on_ground = false;
	}
}

void Player::update(float time, Hero_view* view, float& current_frame)
{
	control(current_frame, time);
	switch (state) 
	{
	case right: dx = speed; break;
	case left: dx = speed; break;
	case up: break;
	case down: dx = 0; break;
	case stay: break;
	}

	if (health <= 0) { life = false; }
	if (life) {
		x += dx * time;
		check_collision_with_map(dx, 0);
		y += dy * time;
		check_collision_with_map(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);

		if (!is_move) { speed = 0; }

		view->set_player_coord_for_view(x, y);
		//if (life) { view->set_player_coord_for_view(x, y); }

		if (!on_ground) dy += 0.0015 * time;
	}
}


Enemy::Enemy(sf::Image& image, sf::String name, TileMap& lev, float x, float y, int w, int h) :
	Entity(image, name, x, y, w, h)
{
	obj = lev.getObjectsByType("solid");
	if (name == "easy_enemy") {
		sprite.setTextureRect(sf::IntRect(0, 4, w, h));
		dx = 0.05;
	}
}

void Enemy::check_collision_with_map(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); ++i) {
		if (get_rect().intersects(obj[i].rect)) {
			//if (obj[i].name == "solid" || obj[i].name == "lucky" || obj[i].name == "tube") {
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; on_ground = true; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; sprite.scale(-1, 1); dx = -0.05; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; sprite.scale(-1, 1); dx = 0.05; }
			//}
		}
		else if(Dy <= 0) on_ground = false;
	}
}

void Enemy::update(float time, Hero_view* view, float& current_frame)
{
	if (name == "easy_enemy") {
		check_collision_with_map(dx, 0);
		x += dx * time;
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) life = false;
	}
}
