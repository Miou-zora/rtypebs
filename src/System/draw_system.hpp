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
#include "zipper.hpp"
#include "raylib.h"

Vector2 vector_to_raylib(vector<float> const &vec)
{
    return (Vector2){vec.x, vec.y};
}

void draw_system(registry &reg,
    sparse_array<component::position> const &positions,
    sparse_array<component::drawable> &sprites)
{
    (void)reg;
    for (auto &&[pos, sprite] : zipper(positions, sprites))
    {
        DrawTextureEx(sprite.value().Drawable, vector_to_raylib(pos.value().Position), 0, sprite.value().scale, WHITE);
    }
}

#endif /* !DRAW_SYSTEM_HPP_ */
