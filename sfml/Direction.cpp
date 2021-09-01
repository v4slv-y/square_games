#include "Direction.h"

void Direction::set_direction()
{
	_direction.x = 0;
	_direction.y = 0;
}

sf::Vector2f Direction::get_direction()
{
	return _direction;
}

void Left::set_direction()
{
	_direction.x -= 15;
	_direction.y = 0;
}

void Right::set_direction()
{
	_direction.x += 15;
	_direction.y = 0;
}

void Top::set_direction()
{
	_direction.x = 0;
	_direction.y -= 15;
}

void Down::set_direction()
{
	_direction.x = 0;
	_direction.y += 15;
}
