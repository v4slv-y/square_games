#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include "Game.h"
#include"Direction.h"
#include"Playground.h"

class Snake :
    public Game
{
    class Apple;
    sf::Clock _clock;
    sf::Time _time;
    sf::Vector2f _body;
    std::vector<sf::Vector2f> _position;
    sf::RectangleShape _one_part;
    const float _side_size = 15;
    Direction* _direction;
    char _direction_version;
    sf::Vector2f _previous_tale_position;
    Playground _playground;
    bool _game_over = false;
public:
    Snake(Playground);

    void moove(const char)override;
    void draw(sf::RenderTarget&)override;
    bool end_game()override;
private:
    bool game_over(bool);
    void direction_selection(const char);
    sf::Vector2f get_head_position();
    void eat();
    bool bite_body();

    class Apple
    {
        sf::RectangleShape _apple;
    public:
        Apple();
        sf::RectangleShape get_apple();
        void put(Playground, Snake);
        sf::Vector2f get_apple_position();
        bool snake_body(sf::Vector2f);
    }new_apple;
};

