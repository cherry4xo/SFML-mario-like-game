#pragma once

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include <SFML/Graphics.hpp>
//#include "hero.h"

class Hero_view : public sf::View {
private:
	float		temp_x, temp_y;

public:
				Hero_view(float x, float y);
	void		set_player_coord_for_view(float x, float y);
	void		viewmap(float time);
	void		change_view();
};

#endif
