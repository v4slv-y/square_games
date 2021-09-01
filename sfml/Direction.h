#pragma once
#include<SFML/Graphics.hpp>

class Direction
{
protected:
	sf::Vector2f _direction;
public:
	virtual void set_direction();
	virtual sf::Vector2f get_direction();
};

class Left :
	public Direction
{
	void set_direction()override;
};

class Right :
	public Direction
{
	void set_direction()override;
};

class Top :
	public Direction
{
	void set_direction()override;
};

class Down :
	public Direction
{
	void set_direction()override;
};