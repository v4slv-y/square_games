#pragma once
#include "Game.h"
#include"Direction.h"
#include"Playground.h"
#include<SFML/Graphics.hpp>
#include<array>

class Tetris :
    public Game
{
	sf::Clock _clock;
	sf::Time _time;
	sf::Vector2f _spawn_point;
	sf::RectangleShape _one_element;
	std::vector<sf::Vector2f> _placed_cubes;
	Direction* _direction = new Down;
	sf::Vector2f _playground_top_left, _playground_down_right;
	bool _end = false;
	
public:
	Tetris(Playground);
	void draw(sf::RenderTarget&);
	void moove(const char);
	bool end_game();

private:
	class Figure
	{
		enum figure_type { CUBE = 1, STICK, AXE, TE }_figure_type;
		std::array<sf::Vector2f, 4> _figure_vertex_position;
		int _type;
	public:
		Figure();
		std::array<sf::Vector2f, 4> get_figure();
		std::array<sf::Vector2f, 4> get_vertex();
		void set_start_position(sf::Vector2f, std::array<sf::Vector2f, 4>);
		void set_start_position(sf::Vector2f);
		void spawn_figure(sf::Vector2f);
		int get_figure_type();
		void rotate_figure(std::array<sf::Vector2f, 4>);
	private:
		void get_firuge_type();
		void get_cube();
		void get_axe();
		void get_stick();
		void get_te();
	}_figure;

	void direction_selection(const char);
	void place_cube(std::array<sf::Vector2f, 4>);
	std::vector<sf::Vector2f> get_placed_cubes();
	void rotate();
	void rotate_axe();
	void rotate_te();
	void rotate_stick();
	bool in_borders(std::array<sf::Vector2f, 4>);
	bool touch_cubes(std::array<sf::Vector2f, 4>);
	void delete_row();
};

