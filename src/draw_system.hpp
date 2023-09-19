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

sf::RenderWindow window(sf::VideoMode(1920, 1080), "B-SRType");

void draw_system(registry &reg,
    sparse_array<component::position> const &positions,
    sparse_array<component::drawable> &sprites)
{
    (void)reg;
    for (size_t i = 0; i < positions.size() && i < sprites.size(); ++i)
    {
        auto &pos = positions[i];
        auto &sprite = sprites[i];

        if (pos.has_value() && sprite.has_value()) {
            sprite.value().draw(window, sf::Vector2f(pos.value().x, pos.value().y));
        }
    }
}

#endif /* !DRAW_SYSTEM_HPP_ */
