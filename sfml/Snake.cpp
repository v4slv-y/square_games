#include "Snake.h"
#include<iostream>

Snake::Snake(Playground pg)
{
	_playground = pg;
	_direction_version = 'r';
	_clock.restart();
	_body.x = _side_size;
	_body.y = _side_size;

	_one_part.setSize(_body);

	sf::Vector2f start(300, 220);

	for (int i = 0; i <= 3; ++i)
	{
		_position.push_back(start);
		start.x -= _side_size;
	}

	new_apple.put(_playground, *this);
}

void Snake::moove(const char option)
{
	sf::Vector2f previous = _position[0];
	_previous_tale_position = _position[_position.size() - 1];

	direction_selection(option);

	_direction->set_direction();

	(*_position.begin()).x += _direction->get_direction().x;
	(*_position.begin()).y += _direction->get_direction().y;


	for (std::vector<sf::Vector2f>::iterator it = _position.begin() + 1; it != _position.end(); ++it)
		std::swap(*it, previous);

	game_over(_playground.out_of_ground(get_head_position()) || bite_body());
	eat();
}

void Snake::draw(sf::RenderTarget& window)
{
	_time = _clock.getElapsedTime();
	if (_time.asSeconds() > 0.5)
	{
		moove(_direction_version);
		_clock.restart();
	}


	for (auto& dr : _position)
	{
		_one_part.setPosition(dr.x, dr.y);
		_one_part.setFillColor(sf::Color::Red);
		window.draw(_one_part);
	}

	window.draw(new_apple.get_apple());
}

bool Snake::end_game()
{
	return _game_over;
}

bool Snake::game_over(bool yes)
{
	_game_over = yes;
	return _game_over;
}

void Snake::direction_selection(const char option)
{
	switch (option)
	{
	case 'l':
		if (_direction_version == 'r')
		{
			_direction = new Right;
			_direction_version = 'r';
			return;
		}
		_direction = new Left;
		_direction_version = 'l';
		break;
	case 'r':
		if (_direction_version == 'l')
		{
			_direction = new Left;
			_direction_version = 'l';
			return;
		}
		_direction = new Right;
		_direction_version = 'r';
		break;
	case 'u':
		if (_direction_version == 'd')
		{
			_direction = new Down;
			_direction_version = 'd';
			return;
		}
		_direction = new Top;
		_direction_version = 'u';
		break;
	case 'd':
		if (_direction_version == 'u')
		{
			_direction = new Top;
			_direction_version = 'u';
			return;
		}
		_direction = new Down;
		_direction_version = 'd';
		break;
	default:
		break;
	}
}

sf::Vector2f Snake::get_head_position()
{
	return sf::Vector2f(_position[0].x, _position[0].y);
}

void Snake::eat()
{
	if (get_head_position() == new_apple.get_apple_position())
	{
		_position.push_back(_previous_tale_position);
		new_apple.put(_playground, *this);
	}
}

bool Snake::bite_body()
{
	for (std::vector<sf::Vector2f>::iterator it = _position.begin() + 2; it != _position.end(); ++it)
		if (_position[0].x == (*it).x && _position[0].y == (*it).y)
			return true;
	return false;
}

Snake::Apple::Apple()
{
	_apple.setFillColor(sf::Color::Green);
	_apple.setSize(sf::Vector2f(15, 15));
}

sf::RectangleShape Snake::Apple::get_apple()
{
	return _apple;
}

void Snake::Apple::put(Playground ground, Snake snake)
{
	int rand_x, rand_y;
	sf::Vector2f points_try;

	do
	{
		rand_x = rand() % (int)snake._position[1].x + 1;
		points_try.x = snake.get_head_position().x + rand_x * 15;
		rand_x = rand() % 20;
		points_try.x -= rand_x * 15;

		rand_y = rand() % (int)snake._position[1].y + 1;
		points_try.y = snake.get_head_position().y + rand_y * 15;
		rand_y = rand() % 15;
		points_try.y -= rand_y * 15;
	} while (ground.out_of_ground(points_try));

	_apple.setPosition(points_try);
}

sf::Vector2f Snake::Apple::get_apple_position()
{
	return _apple.getPosition();
}
