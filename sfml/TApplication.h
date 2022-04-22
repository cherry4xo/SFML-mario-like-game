#pragma once

#ifndef TAPPLCATION_HEADER
#define TAPPLICATION_HEADER

#include "entity.h"

namespace Lesson {
	class TApplication {
	protected:
		sf::RenderWindow*		window;
		Player*					player;
		std::vector<Object>		easy_enemies_objs;
		Hero_view*				hero_view;
		TileMap					lvl;
		//sf::RenderStates*		rdr_states;
		std::list<Entity*> entities;
		std::list<Entity*>::iterator it;
		std::list<Entity*>::iterator it2;
	public:
								TApplication();
								~TApplication();
		void					Init();
		void					Run();
		void					End();
	};
}

#endif