/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** animation_system
*/

#pragma once

#include "registry.hpp"
#include "animation.hpp"
#include "position.hpp"
#include "zipper.hpp"

template<typename T>
static Vector2 vector_to_raylib(vector<T> const &vec) // TODO: move to utils class of raylib
{
    return (Vector2){static_cast<float>(vec.x), static_cast<float>(vec.y)};
}

class animation_system
{
    public:
        animation_system() = default;
        ~animation_system() = default;

        void operator()(registry &r,
            sparse_array<component::animation> &animations,
            sparse_array<component::position> &positions) const
        {
            for (auto &&[anim, pos] : zipper(animations, positions)) {
                if (anim.value().finished)
                    continue;
                anim.value().time += r.get_delta_time();
                if (anim.value().time >= anim.value().frame_times[anim.value().current_frame]) {
                    anim.value().time -= anim.value().frame_times[anim.value().current_frame];
                    anim.value().current_frame++;
                    if (anim.value().current_frame >= anim.value().frames.size()) {
                        if (anim.value().loop) {
                            anim.value().current_frame = 0;
                        } else {
                            anim.value().finished = true;
                            continue;
                        }
                    }
                    anim.value().source_rect.x = anim.value().frames[anim.value().current_frame].x;
                    anim.value().source_rect.y = anim.value().frames[anim.value().current_frame].y;
                }
                Rectangle dest_rect = {
                    static_cast<float>(pos.value().Position.x),
                    static_cast<float>(pos.value().Position.y),
                    static_cast<float>(anim.value().source_rect.width) * anim.value().scale,
                    static_cast<float>(anim.value().source_rect.height) * anim.value().scale
                };
                DrawTexturePro(anim.value().texture, anim.value().source_rect, dest_rect, {0, 0}, 0, WHITE);
            }
        }
};
