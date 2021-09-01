#include "Playground.h"
#include<iostream>

Playground::Playground()
{
	_size.x = 15;
	_size.y = 15;
}

void Playground::draw(sf::RenderTarget& window, Game* game_obj)
{
	sf::VertexArray ground = get_ground_borders();

	window.draw(ground);
	
	game_obj->draw(window);
}

void Playground::menu(int option)
{
	switch (option)
	{
	case SNAKE:
		_field_squares.x = 43;
		_field_squares.y = 25;
		set_field_start_point();
		break;
	case TETRIS:
		_field_squares.x = 12;
		_field_squares.y = 25;
		set_field_start_point();
		break;
	case BLOCK:
		_field_squares.x = 43;
		_field_squares.y = 25;
		set_field_start_point();
		break;
	case MENU:
		set_field_start_point();
		break;
	default:
		break;
	}
}

sf::Vector2f Playground::get_x_edges()
{
	return sf::Vector2f(_playground_start_point.x, _playground_start_point.x + _size.x * _field_squares.x);
}

sf::Vector2f Playground::get_y_edges()
{
	return sf::Vector2f(_playground_start_point.y, _playground_start_point.y + _size.y * _field_squares.y);
}

bool Playground::out_of_ground(sf::Vector2f points)
{
	if (get_x_edges().x < points.x && points.x < (get_x_edges().y - _size.x))
		if (get_y_edges().x < points.y && points.y < (get_y_edges().y - _size.y))
			return false;
	
	return true;
}

void Playground::set_field_start_point()
{
	float x_size = (_size.x * _field_squares.x) / 2;

	_playground_start_point.x = 350 - x_size;
	_playground_start_point.y = 50;
	std::cout << _playground_start_point.x << " = x pg start\n";
	std::cout << _playground_start_point.y << " = x pg start\n";
}

sf::VertexArray Playground::get_ground_borders()
{
	sf::VertexArray ground(sf::LinesStrip, 5);

	sf::Vector2f a, b, c, d, e;

	a.x = _playground_start_point.x;
	a.y = _playground_start_point.y;
	b.x = a.x + _size.x * _field_squares.x;
	b.y = a.y;
	c.x = b.x;
	c.y = b.y + _size.y * _field_squares.y;
	d.x = a.x;
	d.y = c.y;
	e.x = a.x;
	e.y = a.y;

	ground[0].position = a;
	ground[1].position = b;
	ground[2].position = c;
	ground[3].position = d;
	ground[4].position = e;

	ground[0].color = sf::Color::White;
	ground[1].color = sf::Color::White;
	ground[2].color = sf::Color::White;
	ground[3].color = sf::Color::White;
	ground[4].color = sf::Color::White;

	return ground;
}

float Playground::get_center()
{
	_center = (_size.x * _field_squares.x) / 2 + _playground_start_point.x;

	return _center;
}

sf::Vector2f Playground::get_field_start_point()
{
	return _playground_start_point;
}
