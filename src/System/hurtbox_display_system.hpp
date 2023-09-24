/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** hurtbox_display_system
*/

#pragma once

#include "registry.hpp"
#include "collider.hpp"
#include "displayable_hurtbox.hpp"
#include "indexed_zipper.hpp"
#include "draw_system.hpp"

void hurtbox_display_system(registry &reg,
                    sparse_array<component::collider> const &colliders,
                    sparse_array<component::displayable_hurtbox> const &displayable_hurtboxes,
                    sparse_array<component::position> const &positions)
{
    (void)reg;
    for (auto &&[i, hb, displayable_hb, pos] : indexed_zipper(colliders, displayable_hurtboxes, positions))
    {
        if (!displayable_hb.value().is_displayed)
            continue;
        sf::RectangleShape hurtbox(sf::Vector2f(hb.value().width, hb.value().height));
        hurtbox.setFillColor(sf::Color::Transparent);
        hurtbox.setOutlineColor(hb.value().collided_with.empty() ? sf::Color::Green : sf::Color::Red);
        hurtbox.setOutlineThickness(1);
        sf::Transform transform;
        transform.translate(pos.value().Position.x, pos.value().Position.y);
        window.draw(hurtbox, transform);
    }
}
