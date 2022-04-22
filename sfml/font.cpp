#include "font.h"

myFont::myFont() :
	font(),
	text(),
	font_file_path("PoppkornRegular.ttf"),
	font_size(20),
	string_text(string_text)
{
	font.loadFromFile(font_file_path);
	text.setString("");
	text.setCharacterSize(20);
	text.setFont(font);
	text.setColor(sf::Color(191, 76, 240));
}

myFont::myFont(sf::String font_file_path, sf::String string_text, int font_size, sf::Color color) :
	font(),
	text(),
	font_size(font_size),
	font_file_path(font_file_path),
	string_text(string_text)
{
	font.loadFromFile(font_file_path);
	text.setString(string_text);
	text.setFont(font);
	text.setCharacterSize(font_size);
	text.setColor(color);
}

sf::String myFont::get_text() { return this->string_text; }

void myFont::set_color(sf::Color color) { text.setColor(color); }
void myFont::set_font(sf::String font_file_path)
{	
	sf::Font newFont;
	newFont.loadFromFile(font_file_path);
	text.setFont(newFont); 
}
void myFont::set_text(sf::String string_text) { text.setString(string_text); this->string_text = string_text; }

void myFont::Draw(sf::RenderWindow* window, Hero_view* view, float x, float y, Hero* hero)
{
	std::ostringstream player_score_string;
	player_score_string << hero->get_score();
	this->set_text("Picked up: " + player_score_string.str());
	this->text.setPosition(view->getCenter().x + x, view->getCenter().y + y);
	window->draw(text);
}