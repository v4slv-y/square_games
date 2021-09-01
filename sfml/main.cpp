#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include"Playground.h"
#include"Snake.h"
#include"Tetris.h"
#include"Block.h"
#include"Menu.h"
#include"Direction.h"


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(700, 450), "window", sf::Style::Default, settings);
    Game* game_ptr;
    game_ptr = new Menu;
    Playground pg;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                    pg.menu(0);
                    std::cout << "snake\n";
                    game_ptr = new Snake(pg);
                }
                if (event.key.code == sf::Keyboard::Num2)
                {
                    pg.menu(1);
                    std::cout << "tetris\n";
                    game_ptr = new Tetris(pg);
                }
                if (event.key.code == sf::Keyboard::Num3)
                {
                    pg.menu(2);
                    std::cout << "block\n";
                    game_ptr = new Block(pg);
                }
                if (event.key.code == sf::Keyboard::Num9)
                {
                    pg.menu(9);
                    std::cout << "menu\n";
                    game_ptr = new Menu;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    game_ptr->moove('u');
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    game_ptr->moove('d');
                }
                if (event.key.code == sf::Keyboard::Left)
                {
                    game_ptr->moove('l');
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    game_ptr->moove('r');
                }
                if (event.key.code == sf::Keyboard::A)
                {
                    std::cout << rand() % -100 + 100;
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        pg.draw(window, game_ptr);

        if (game_ptr->end_game())
            game_ptr = new Menu;

        window.display();
    }

    delete game_ptr;
    return 0;
}