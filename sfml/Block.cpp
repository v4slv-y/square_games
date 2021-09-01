#include "Block.h"
#include<iostream>
#include<vector>

Block::Block(Playground pg)
{
    _pg = pg;
    sf::VertexArray pl(sf::Lines, 2);
    pl[0].position.x = pg.get_field_start_point().x + 200;
    pl[0].position.y = pg.get_field_start_point().y + 15 * 25;

    pl[1].position.x = pl[0].position.x + 150;
    pl[1].position.y = pl[0].position.y; 

    pl[0].color = sf::Color::Red;
    pl[1].color = sf::Color::Blue;
    _platform = pl;

    _shell.setFillColor(sf::Color::Red);
    _shell.setRadius(5);
    _shell.setPosition(sf::Vector2f(pg.get_center(), pl[0].position.y - 25));
    _shell.setOutlineColor(sf::Color::Blue);

    _direction.x = 1;
    _direction.y = -1;

    std::cout << "platform 0 x = " << pl[0].position.x << "; platform 0 y = " << pl[0].position.y << '\n';
    std::cout << "platform 1 x = " << pl[1].position.x << "; platform 1 y = " << pl[1].position.y << '\n';

    draw_blocks();
}

void Block::draw(sf::RenderTarget& window)
{
    for (auto& b : _blocks)
        window.draw(b);

    _timer = _clock.getElapsedTime();
    if (_timer.asMilliseconds() > 5)
    {
        hit();
        set_vector();
        _clock.restart();
    }

    window.draw(_platform);
    window.draw(_shell);
}

void Block::moove(const char direction)
{
    switch (direction)
    {
    case 'l':
        if (_pg.get_field_start_point().x + _velocity > _platform[0].position.x)
        {
            _platform[0].position.x = _pg.get_field_start_point().x;
            _platform[1].position.x = _platform[0].position.x + 150;
        }
        else
            moove_platform(-_velocity);
        break;
    case 'r':
        if ((_pg.get_field_start_point().x + 15 * 43)-_velocity < _platform[1].position.x)
        {
            _platform[1].position.x = _pg.get_field_start_point().x + 15 * 43;
            _platform[0].position.x = _platform[1].position.x - 150;
        }
        else
            moove_platform(_velocity);
        break;
    default:
        break;
    }
}

bool Block::end_game()
{
    return false;
}

void Block::hit()
{
    sf::Vector2f center;
    center.x = _shell.getPosition().x + 5;
    center.y = _shell.getPosition().y + 5;

    float right = _pg.get_field_start_point().x + 15 * 43;

    if (center.x < _pg.get_field_start_point().x + 5)
        hit_processing(center);
    else if (center.x > _pg.get_field_start_point().x + 15 * 43 - 5)
        hit_processing(center);
    else if (center.y < _pg.get_field_start_point().y + 5)
        hit_processing(center);
    else if (center.x >= _platform[0].position.x && center.x <= _platform[1].position.x && center.y > _platform[0].position.y - 5)
        hit_processing(center);

    if (center.y < _pg.get_field_start_point().y + 220)
        hit_block(center);
}

void Block::set_vector()
{
    sf::Vector2f new_pos = _shell.getPosition();
    new_pos += _direction;

    _shell.setPosition(new_pos);
}

void Block::hit_processing(sf::Vector2f center)
{
    sf::Vector2f orig_direction = center;
    sf::Vector2f prev_position;
    std::vector<sf::Vector2f> vectors;

    prev_position.x = center.x + -_direction.x;
    prev_position.y = center.y + -_direction.y;

    orig_direction.x += 1;
    orig_direction.y += 1;
    vectors.push_back(orig_direction);
    orig_direction = center;

    orig_direction.x += 1;
    orig_direction.y -= 1; 
    vectors.push_back(orig_direction);
    orig_direction = center;

    orig_direction.x -= 1;
    orig_direction.y += 1;
    vectors.push_back(orig_direction);
    orig_direction = center;

    orig_direction.x -= 1;
    orig_direction.y -= 1;
    vectors.push_back(orig_direction);
    orig_direction = center;

    for (auto& next : vectors)
        if (next != prev_position && !out_of_range(next))
        {
            _direction.x = next.x - center.x;
            _direction.y = next.y - center.y;

            return;
        }
}

bool Block::out_of_range(sf::Vector2f center)
{
    if (center.x<_pg.get_field_start_point().x + 5 || center.x>_pg.get_field_start_point().x + 15 * 43 - 5 ||
        center.y<_pg.get_field_start_point().y + 5 || center.y>_platform[0].position.y - 5)
        return true;

    return false;
}

void Block::draw_blocks()
{
    sf::VertexArray quad(sf::Quads, 4);
    sf::Vector2f zero_point = _pg.get_field_start_point();
    zero_point.x += 12;
    zero_point.y += 5;

    do
    {
        quad[0].position = zero_point;
        quad[1].position = sf::Vector2f(quad[0].position.x + 21, quad[0].position.y);
        quad[2].position = sf::Vector2f(quad[1].position.x, quad[1].position.y + 21);
        quad[3].position = sf::Vector2f(quad[2].position.x - 21, quad[2].position.y);

        quad[0].color = sf::Color::Yellow;
        quad[1].color = sf::Color::Yellow;
        quad[2].color = sf::Color::Yellow;
        quad[3].color = sf::Color::Yellow;

        zero_point.x += 25;

        if (zero_point.x >= _pg.get_field_start_point().x + 15 * 43 - 30)
        {
            zero_point.x = _pg.get_field_start_point().x + 12;
            zero_point.y += 25;
        }
        
        _blocks.push_back(quad);

    } while (zero_point.y < _pg.get_field_start_point().y + 200);
}

void Block::hit_block(sf::Vector2f center)
{
    center.x += _direction.x * 5;
    center.y += _direction.y * 5;

    for (std::vector<sf::VertexArray>::reverse_iterator riter = _blocks.rbegin(); riter != _blocks.rend(); ++riter)
    {
        if ((*riter)[0].position.x <= center.x && (*riter)[0].position.x + 21 >= center.x &&
            (*riter)[0].position.y <= center.y && (*riter)[0].position.y + 21 >= center.y)
        {
            
        }
    }
}

void Block::moove_platform(int velocity)
{
    for (int i = 0; i < 2; ++i)
    {
        _platform[0].position.x += velocity;
        _platform[1].position.x += velocity;
    }
}
