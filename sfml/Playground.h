#pragma once
#include <SFML/Graphics.hpp>
#include"Game.h"

class Playground //700, 450
{
	enum { SNAKE, TETRIS, BLOCK, MENU = 9 };
	sf::Vector2f _size;
	sf::Vector2f _playground_start_point;
	sf::Vector2f _field_squares;
	float _center;
public:
	Playground();
	void draw(sf::RenderTarget&, Game*);
	void menu(int);
	bool out_of_ground(sf::Vector2f);
	float get_center();
	sf::Vector2f get_field_start_point();
private:
	void set_field_start_point();
	sf::Vector2f get_x_edges();
	sf::Vector2f get_y_edges();
	sf::VertexArray get_ground_borders();
};

