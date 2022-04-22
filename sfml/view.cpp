#include "view.h"

Hero_view::Hero_view(float x, float y) :
	sf::View(),
	temp_x(x),
	temp_y(y) 
{ this->set_player_coord_for_view(x, y); }

void Hero_view::set_player_coord_for_view(float x, float y)
{
	temp_x = x;
	temp_y = y;

	if (x < 192) temp_x = 192;
	//if (y < 32) temp_y = 32;
	//if (y > 600 - 64) temp_y = 600 - 64;
	if (x > 3166) temp_x = 3166;

	this->setCenter(temp_x + 8, 170);
}

void Hero_view::viewmap(float time)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { this->move(0.2, 0 * time); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { this->move(0, 0.2 * time); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { this->move(-0.2 * time, 0); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { this->move(0, -0.2 * time); }
}

void Hero_view::change_view()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) { this->zoom(1.006f); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { this->zoom(0.994f); }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) { this->setSize(800, 800); }
}
