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
    struct drawable
    {
        drawable(std::shared_ptr<sf::Drawable> _drawable) : Drawable(_drawable) {}
        std::shared_ptr<sf::Drawable> Drawable;
    };
};

#endif /* !DRAWABLE_HPP_ */
