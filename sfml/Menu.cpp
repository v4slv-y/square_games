#include "Menu.h"

void Menu::draw(sf::RenderTarget& window)
{
	sf::CircleShape cc;
	cc.setRadius(20);
	cc.setPosition(50, 50);
	cc.setFillColor(sf::Color::Green);
	window.draw(cc);
}

void Menu::moove(const char)
{
}

bool Menu::end_game()
{
	return false;
}
