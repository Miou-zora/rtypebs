/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace component
{
    class drawable // TODO: think about a better class / maybe a struct
    {
    public:
        drawable()
        {
            _shape.setSize(sf::Vector2f(50, 50));
            _shape.setFillColor(sf::Color::White);
        }

        virtual ~drawable() = default;

        void draw(sf::RenderWindow &window, sf::Vector2f pos)
        {
            _shape.setPosition(pos);
            window.draw(_shape);
        }

    protected:
        sf::RectangleShape _shape;
    };
};

#endif /* !DRAWABLE_HPP_ */
