/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** draw_system
*/

#ifndef DRAW_SYSTEM_HPP_
#define DRAW_SYSTEM_HPP_

#include "registry.hpp"
#include "drawable.hpp"
#include "position.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "zipper.hpp"

sf::RenderWindow window(sf::VideoMode(1920, 1080), "B-SRType");

void draw_system(registry &reg,
    sparse_array<component::position> const &positions,
    sparse_array<component::drawable> &sprites)
{
    (void)reg;
    for (auto &&[pos, sprite] : zipper(positions, sprites))
    {
        if (sprite.value().Drawable == nullptr)
            continue;
        sf::Transform transform;
        transform.translate(pos.value().x, pos.value().y);

        window.draw(*sprite.value().Drawable, transform);
    }
}

#endif /* !DRAW_SYSTEM_HPP_ */
