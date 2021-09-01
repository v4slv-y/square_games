#pragma once
#include "Game.h"
#include"Playground.h"

class Block :
    public Game
{
	sf::Clock _clock;
	sf::Time _timer;
	sf::VertexArray _platform;
	sf::CircleShape _shell;
	sf::Vector2f _direction;
	int _velocity = 5;
	Playground _pg;
	std::vector<sf::VertexArray> _blocks;

public:
	Block(Playground);
	void draw(sf::RenderTarget&)override;
	void moove(const char)override;
	bool end_game()override;
private:
	void moove_platform(int);
	void set_vector();
	void hit_processing(sf::Vector2f);
	void hit();
	bool out_of_range(sf::Vector2f);
	void hit_block(sf::Vector2f);
	void draw_blocks();
};