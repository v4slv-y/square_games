#pragma once
#include <SFML/Graphics.hpp>
#include<vector>

class Game
{
public:
	virtual void draw(sf::RenderTarget&) = 0;
	virtual void moove(const char) = 0;
	virtual bool end_game() = 0;
};

