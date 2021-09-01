#include "Tetris.h"
#include<iostream>
#include<algorithm>

Tetris::Tetris(Playground ground)//12,25
{
	_spawn_point.x = ground.get_center();
	_spawn_point.y = 50;

	_playground_down_right = _playground_top_left = ground.get_field_start_point();
	std::cout << "top left x=" << _playground_top_left.x << '\n';
	std::cout << "top left y=" << _playground_top_left.y << '\n';

	for (int i = 1; i < 12; ++i)
		_playground_down_right.x += 15;
	_playground_down_right.y = _playground_top_left.y;
	for (int i = 0; i < 24; ++i)
		_playground_down_right.y += 15;

	std::cout << "down right x=" << _playground_down_right.x << '\n';
	std::cout << "down right y=" << _playground_down_right.y << '\n';

	_figure.set_start_position(_spawn_point);

	_one_element.setFillColor(sf::Color::Yellow);
	_one_element.setSize(sf::Vector2f(15, 15));
}

void Tetris::draw(sf::RenderTarget& window)
{
	_time = _clock.getElapsedTime();
	if (_time.asSeconds() > 0.5)
	{
		moove('d');
		_clock.restart();
	}

	for (auto& elem : _figure.get_vertex())
	{
		_one_element.setPosition(elem);
		window.draw(_one_element);
	}

	for (auto& cube : get_placed_cubes())
	{
		_one_element.setPosition(cube);
		window.draw(_one_element);
	}
}

void Tetris::moove(const char direction)
{
	direction_selection(direction);

	_direction->set_direction();

	for (auto& placed : _placed_cubes)
		for (auto& vertex : _figure.get_vertex())
			if (vertex.y == placed.y - 15 && vertex.x == placed.x)
			{
				place_cube(_figure.get_vertex());
				_figure.spawn_figure(_spawn_point);
				delete_row();
				return;
			}

	_figure.set_start_position(_direction->get_direction(), _figure.get_vertex());

	for (auto& vertex : _figure.get_vertex())
		if (vertex.y == _playground_down_right.y)
		{
			std::cout << "floor!\n";
			std::cout << "figure x=" << _figure.get_vertex()[0].x << '\n';
			std::cout << "figure y=" << _figure.get_vertex()[0].y << '\n';
			for (auto& cub : _figure.get_vertex())
				std::cout << " x = " << cub.x << " y = " << cub.y << '\n';

			place_cube(_figure.get_vertex());
			_figure.spawn_figure(_spawn_point);
			delete_row();
			return;
		}

	std::cout << "figure x=" << _figure.get_vertex()[0].x << '\n';
	std::cout << "figure y=" << _figure.get_vertex()[0].y << '\n';
}

void Tetris::direction_selection(const char direction)
{
	switch (direction)
	{
	case 'u':
		for (auto& vertex : _figure.get_vertex())
			if (vertex.y == _playground_down_right.y-15)
			{
				_direction = new Down;
				return;
			}
		rotate();
		_direction = new Down;
		break;
	case 'd':
		_direction = new Down;
		break;
	case 'l':
		for (auto& vertex : _figure.get_vertex())
			if (vertex.x == _playground_top_left.x)
			{
				std::cout << "left wall!\n";
				_direction = new Down;
				return;
			}
		for (auto& vertex : _figure.get_vertex())
		{
			for(auto&placed:_placed_cubes)
				if (vertex.y == placed.y && vertex.x == placed.x + 15)
				{
					_direction = new Down;
					return;
				}
		}
		_direction = new Left;
		break;
	case 'r':
		for (auto& vertex : _figure.get_vertex())
			if (vertex.x == _playground_down_right.x)
			{
				std::cout << "right wall!\n";
				_direction = new Down;
				return;
			}
		for (auto& vertex : _figure.get_vertex())
		{
			for (auto& placed : _placed_cubes)
				if (vertex.y==placed.y && vertex.x == placed.x - 15)
				{
					_direction = new Down;
					return;
				}
		}
		_direction = new Right;
		break;
	default:
		break;
	}
}

void Tetris::place_cube(std::array<sf::Vector2f, 4> cubes)
{
	for (auto& place : cubes)
	{
		_placed_cubes.push_back(place);
		if (place.y == _playground_top_left.y)
			_end = true;
	}
}

std::vector<sf::Vector2f> Tetris::get_placed_cubes()
{
	return _placed_cubes;
}

void Tetris::rotate()
{
	switch (_figure.get_figure_type())
	{
	case 2:
		rotate_stick();
		break;
	case 3:
		rotate_axe();
		break;
	case 4:
		rotate_te();
		break;
	default:
		break;
	}
}

void Tetris::rotate_axe()
{
	std::array<sf::Vector2f, 4> copy = _figure.get_vertex();
	if (copy[1].y == copy[0].y && copy[1].x == (copy[0].x - 15))
	{
		copy[1].x = copy[0].x;
		copy[1].y = copy[0].y - 15;

		copy[2].x = copy[0].x;
		copy[2].y = copy[0].y + 15;

		copy[3].x = copy[0].x - 15;
		copy[3].y = copy[0].y + 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[1].x == copy[0].x && copy[1].y == copy[0].y - 15)
	{
		copy[1].x = copy[0].x + 15;
		copy[1].y = copy[0].y;

		copy[2].x = copy[0].x - 15;
		copy[2].y = copy[0].y;

		copy[3].x = copy[2].x;
		copy[3].y = copy[0].y - 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[1].y == copy[0].y && copy[1].x == copy[0].x + 15)
	{
		copy[1].x = copy[0].x;
		copy[1].y = copy[0].y + 15;

		copy[2].x = copy[0].x;
		copy[2].y = copy[0].y - 15;

		copy[3].x = copy[2].x + 15;
		copy[3].y = copy[2].y;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[1].x == copy[0].x && copy[1].y == copy[0].y + 15)
	{
		copy[1].x = copy[0].x - 15;
		copy[1].y = copy[0].y;

		copy[2].x = copy[0].x + 15;
		copy[2].y = copy[0].y + 15;

		copy[3].x = copy[2].x;
		copy[3].y = copy[2].y - 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
}

void Tetris::rotate_te()
{
	std::array<sf::Vector2f, 4> copy = _figure.get_vertex();
	if (copy[1].x == copy[0].x - 15 && copy[1].y == copy[0].y)//sprava
	{
		std::cout << "sprava\n";
		copy[1].x = copy[0].x;
		copy[1].y = copy[0].y - 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[3].x == copy[0].x && copy[3].y == copy[0].y + 15)//sverhu
	{
		std::cout << "sverhu\n";
		copy[3].x = copy[0].x - 15;
		copy[3].y = copy[0].y;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[2].y == copy[0].y && copy[2].x == copy[0].x + 15)//sleva
	{
		std::cout << "sleva\n";
		copy[2].x = copy[0].x;
		copy[2].y = copy[0].y + 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
	else if (copy[2].x == copy[0].x && copy[2].y == copy[0].y + 15)
	{
		copy[1].x = copy[0].x - 15;
		copy[1].y = copy[0].y;

		copy[2].x = copy[0].x + 15;
		copy[2].y = copy[0].y;

		copy[3].x = copy[0].x;
		copy[3].y = copy[0].y + 15;

		if (in_borders(copy) || touch_cubes(copy))
			return;

		_figure.rotate_figure(copy);
	}
}

void Tetris::rotate_stick()
{
	std::array<sf::Vector2f, 4> copy = _figure.get_vertex();
	if (copy[1].x < copy[0].x)
	{
		copy[1].x = copy[0].x;
		copy[1].y = copy[0].y - 15;

		copy[2].x = copy[0].x;
		copy[2].y = copy[0].y - 30;

		copy[3].x = copy[0].x;
		copy[3].y = copy[0].y + 15;
	}
	else if (copy[1].x == copy[0].x)
	{
		copy[1].x = copy[0].x - 15;
		copy[1].y = copy[0].y;

		copy[2].x = copy[0].x - 30;
		copy[2].y = copy[0].y;

		copy[3].x = copy[0].x + 15;
		copy[3].y = copy[0].y;
	}

	if (in_borders(copy) || touch_cubes(copy))
		return;

	_figure.rotate_figure(copy);
}

bool Tetris::in_borders(std::array<sf::Vector2f, 4> figure)
{
	for (auto& element : figure)
		if (element.x<_playground_top_left.x || element.x>_playground_down_right.x 
			|| element.y < _playground_top_left.y || element.y > _playground_down_right.y)
			return true;

	return false;
}

bool Tetris::touch_cubes(std::array<sf::Vector2f, 4> figure)
{
	for (auto& element : figure)
	{
		for (auto& placed : _placed_cubes)
		{
			if (element.x == placed.x && element.y == placed.y)
				return true;
		}
	}

	return false;
}

void Tetris::delete_row()
{
	std::vector<sf::Vector2f> must_delete;

	for (int y = _playground_down_right.y; y > _playground_top_left.y;)
	{
		for (int x = _playground_top_left.x; x <= _playground_down_right.x; x += 15)
		{
			for (auto placed : _placed_cubes)
				if (placed.y == y && placed.x == x)
					must_delete.push_back(placed);
		}
		if (must_delete.size() == 12)
		{
			auto result = std::remove_if(_placed_cubes.begin(), _placed_cubes.end(), [=](const sf::Vector2f& vec) {return vec.y == y; });
			_placed_cubes.erase(result, _placed_cubes.end());

			for (auto& drop : _placed_cubes)
				if (drop.y < y)
					drop.y += 15;
		}
		else
			y -= 15;
		must_delete.clear();
	}
}

bool Tetris::end_game()
{
	return _end;
}

Tetris::Figure::Figure()
{
	_type = rand() % 3 + 1;
}

std::array<sf::Vector2f, 4> Tetris::Figure::get_figure()
{
	get_firuge_type();

	return _figure_vertex_position;
}

std::array<sf::Vector2f, 4> Tetris::Figure::get_vertex()
{
	return _figure_vertex_position;
}

void Tetris::Figure::set_start_position(sf::Vector2f start, std::array<sf::Vector2f, 4> new_position )
{
	_figure_vertex_position[0].x += start.x;
	_figure_vertex_position[0].y += start.y;

	_figure_vertex_position[1].x += start.x;
	_figure_vertex_position[1].y += start.y;

	_figure_vertex_position[2].x += start.x;
	_figure_vertex_position[2].y += start.y;

	_figure_vertex_position[3].x += start.x;
	_figure_vertex_position[3].y += start.y;
}

void Tetris::Figure::set_start_position(sf::Vector2f start)
{
	_figure_vertex_position[0].x += start.x;
	_figure_vertex_position[0].y += start.y;

	get_firuge_type();
}

void Tetris::Figure::spawn_figure(sf::Vector2f start_point)
{
	_type = rand() % 4 + 1;

	_figure_vertex_position[0].x = 0;
	_figure_vertex_position[0].y = 0;

	set_start_position(start_point);
	get_firuge_type();
}

int Tetris::Figure::get_figure_type()
{
	return _type;
}

void Tetris::Figure::rotate_figure(std::array<sf::Vector2f, 4> new_position)
{
	_figure_vertex_position = new_position;
}

void Tetris::Figure::get_firuge_type()//{ CUBE = 1, STICK, AXE, TE };
{
	switch (_type)
	{
	case CUBE:
		get_cube();
		break;
	case STICK:
		get_stick();
		break;
	case AXE:
		get_axe();
		break;
	case TE:
		get_te();
		break;
	default:
		break;
	}
}

void Tetris::Figure::get_cube()
{
	_figure_vertex_position[1].x = 15 + _figure_vertex_position[0].x;
	_figure_vertex_position[1].y = _figure_vertex_position[0].y;

	_figure_vertex_position[2].x = _figure_vertex_position[1].x;
	_figure_vertex_position[2].y = 15 + _figure_vertex_position[1].y;

	_figure_vertex_position[3].x = _figure_vertex_position[0].x;
	_figure_vertex_position[3].y = _figure_vertex_position[2].y;
}

void Tetris::Figure::get_axe()
{
	_figure_vertex_position[1].x = _figure_vertex_position[0].x - 15;
	_figure_vertex_position[1].y = _figure_vertex_position[0].y;

	_figure_vertex_position[2].x = _figure_vertex_position[0].x + 15;
	_figure_vertex_position[2].y = _figure_vertex_position[0].y;

	_figure_vertex_position[3].x = _figure_vertex_position[2].x;
	_figure_vertex_position[3].y = _figure_vertex_position[2].y + 15;
}

void Tetris::Figure::get_stick()
{
	_figure_vertex_position[1].x = _figure_vertex_position[0].x - 15;
	_figure_vertex_position[1].y = _figure_vertex_position[0].y;

	_figure_vertex_position[2].x = _figure_vertex_position[1].x - 15;
	_figure_vertex_position[2].y = _figure_vertex_position[1].y;

	_figure_vertex_position[3].x = _figure_vertex_position[0].x + 15;
	_figure_vertex_position[3].y = _figure_vertex_position[2].y;
}

void Tetris::Figure::get_te()
{
	_figure_vertex_position[1].x = _figure_vertex_position[0].x - 15;
	_figure_vertex_position[1].y = _figure_vertex_position[0].y;

	_figure_vertex_position[2].x = _figure_vertex_position[0].x + 15;
	_figure_vertex_position[2].y = _figure_vertex_position[0].y;

	_figure_vertex_position[3].x = _figure_vertex_position[0].x;
	_figure_vertex_position[3].y = _figure_vertex_position[0].y + 15;
}