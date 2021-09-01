#pragma once
#include "Game.h"
class Menu :
    public Game
{
public:
    void draw(sf::RenderTarget&)override;
    void moove(const char)override;
    bool end_game();
};

