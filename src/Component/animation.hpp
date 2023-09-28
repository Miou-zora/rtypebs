/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** animation
*/

#pragma once

#include "raylib.h"
#include <vector>
#include "vector.hpp"

namespace component
{
    struct animation
    {
        Texture2D texture; // Texture of the animation
        float scale; // Scale to display
        Rectangle source_rect; // Size of a frame
        std::vector<vector<int>> frames; // Position of each frames
        std::vector<float> frame_times; // Time of each frames
        std::size_t current_frame; // Index of the current frame
        float time; // Time since the last frame
        bool loop; // If the animation should loop
        bool finished; // If the animation is finished
    };
}
