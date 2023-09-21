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
        drawable(std::shared_ptr<sf::Drawable> drawable_instance) : _drawable(drawable_instance)
        {

        }

        ~drawable() = default;

        void draw(sf::RenderWindow &window, sf::Vector2f pos)
        {
            if (!_drawable)
                return;
            sf::Transform transform;

            transform.translate(pos);
            window.draw(*_drawable, transform);
        }

    private:
        std::shared_ptr<sf::Drawable> _drawable;
    };
};

#endif /* !DRAWABLE_HPP_ */
