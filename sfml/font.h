#pragma once
#pragma warning(once: 4996)
#include "main.h"
#include "view.h"
//#include "hero.h"
#include <sstream>

class myFont
{
protected:
	sf::Font			font;
	sf::Text			text;
	sf::String			font_file_path;
	sf::String			string_text;
	int					font_size;
public:
						myFont();
						myFont(sf::String font_file_path, sf::String string_text, int font_size, sf::Color font_color);

	sf::String			get_text();

	void				set_font(sf::String font_file_path);
	void				set_text(sf::String string_text);
	void				set_color(sf::Color color);

	void				Draw(sf::RenderWindow* window, Hero_view* view, float x, float y, Hero* hero);
};