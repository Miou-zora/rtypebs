/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** displayable_hurtbox
*/

#pragma once

namespace component
{
    struct displayable_hurtbox {
        displayable_hurtbox(bool _is_displayed = false) : is_displayed(_is_displayed) {};
        ~displayable_hurtbox() = default;

        bool is_displayed;
    };
};
