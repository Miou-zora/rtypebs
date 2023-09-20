/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include <SFML/Graphics.hpp>

namespace component
{
    class controllable // TODO: think about a better class / maybe a struct
    {
    public:
        controllable() = default;
        ~controllable() = default;

        bool is_key_up_pressed() const
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        }

        bool is_key_down_pressed() const
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        }

        bool is_key_left_pressed() const
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        }

        bool is_key_right_pressed() const
        {
            return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        }
    };
};

#endif /* !CONTROLLABLE_HPP_ */
