#include "TApplication.h"

namespace Lesson {
	TApplication::TApplication() :
		window(nullptr),
		player(nullptr),
		//easy_enemy(nullptr),
		hero_view(nullptr),
		lvl()
		//rdr_states(nullptr)
	{}

	TApplication::~TApplication() {}

	void TApplication::Init() {
		lvl.load("C:/Users/User/source/repos/sfml/sfml/source/misctmx.tmx");

		window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mario-like");

		hero_view = new Hero_view(250, 250);
		hero_view->reset(sf::FloatRect(0, 0, 800, 600));

		sf::Image player_image;
		player_image.loadFromFile("source/mario_sprites/mario.png");
		sf::Image enemy_image;
		enemy_image.loadFromFile("source/mario_sprites/enemies.png");

		Object player_obj = lvl.getObject("player");
		easy_enemies_objs = lvl.getObjectsByName("easy_enemy");

		for (int i = 0; i < easy_enemies_objs.size(); ++i) {
			entities.push_back(new Enemy(enemy_image, "easy_enemy", lvl, easy_enemies_objs[i].rect.left, easy_enemies_objs[i].rect.top, 16, 16));
		}

		player = new Player(player_image, "Player1", lvl, player_obj.rect.left, player_obj.rect.top, 16, 17);

			
	}

	void TApplication::Run() {

		float current_frame = 0;
		float health_timer = 10;
		sf::Clock clock;
		hero_view->zoom(0.5f);

		while (window->isOpen() && !(player->win) && (player->life)) {

			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time /= 1200;

			sf::Event e;
			while (window->pollEvent(e)) {
				if (e.type == sf::Event::Closed)
					window->close();
			}

			sf::RenderStates* rdr_states;
			rdr_states = new sf::RenderStates();

			window->setView(*hero_view);
			window->clear(sf::Color(255, 255, 255));

			player->update(time, hero_view, current_frame);
			for (it = entities.begin(); it != entities.end();) {
				Entity* b = *it;
				b->update(time, hero_view, current_frame);
				if (b->life == false) { it = entities.erase(it); delete b; }
				else it++;
			}
			for (it = entities.begin(); it != entities.end(); ++it) {
				if ((*it)->get_rect().intersects(player->get_rect())) {
					if ((*it)->name == "easy_enemy") {
						if (player->get_d().second > 0 && player->get_on_ground() == false) {
							(*it)->set_d(0, 0); player->set_d(0, -0.3); (*it)->health = 0;
						}
						if ((*it)->get_d().first > 0) {
							(*it)->set_x(player->get_rect().left - (*it)->get_rect().width);
							(*it)->set_d(0, 0);
							if (int(health_timer) == 10) {
								health_timer = 0;
								player->change_health(-5);
							}
						}
						if ((*it)->get_d().first < 0) {
							(*it)->set_x(player->get_rect().left + player->get_rect().width);
							(*it)->set_d(0, 0);
							if (int(health_timer) == 10) {
								health_timer = 0;
								player->change_health(-5);
							}
						}
						if (player->get_d().first > 0) {
							player->set_x((*it)->get_rect().left - player->get_rect().width);
							//player->set_d(0.5, -0.3);
							if (int(health_timer) == 10) {
								health_timer = 0;
								player->change_health(-5);
							}
						}
						if (player->get_d().first < 0) { 
							player->set_x((*it)->get_rect().left + (*it)->get_rect().width); 
							//player->set_d(0.5, -0.3);
							if (int(health_timer) == 10) {
								health_timer = 0;
								player->change_health(-5);
							}
						}
						
					}
				}
				for (it2 = entities.begin(); it2 != entities.end(); ++it2) {
					if ((*it)->get_rect() != (*it2)->get_rect()) {
						if (((*it)->get_rect().intersects((*it2)->get_rect())) && ((*it)->name == "easy_enemy") && ((*it2)->name == "easy_enemy"))//если столкнулись два объекта и они враги
						{
							(*it)->set_d((*it)->get_d().first * -1, 0);
							(*it)->sprite.scale(-1, 1);
						}
					}
				}
			}
			health_timer += 0.007 * time;
			if (int(health_timer) > 9) health_timer = 10;
			for (it = entities.begin(); it != entities.end(); it++)
				(*it)->update(time, hero_view, current_frame);
			window->draw(lvl);
			for (it = entities.begin(); it != entities.end(); ++it) {
				window->draw((*it)->sprite);
			}
			player->Draw(window);

			window->display();
		}
	}

	void TApplication::End() {
		if (window != nullptr) {
			delete window;
			window = nullptr;
		}
		/*if (map_widget != nullptr) {
			delete map_widget;
			map_widget = nullptr;
		}*/
		if (player != nullptr) {
			delete player;
			player = nullptr;
		}
		if (hero_view != nullptr) {
			delete hero_view;
			hero_view = nullptr;
		}
		/*if (easy_enemy != nullptr) {
			delete easy_enemy;
			easy_enemy = nullptr;
		}*/
	}
}