/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** playerShooter
*/

#pragma once

#include "shooter.hpp"

namespace component
{
    class playerShooter : public shooter {
        public:
            playerShooter(const std::string &projectileName_, float _cooldown = 1) : shooter(projectileName_, _cooldown) {};

            bool canShoot(void) override
            {
                return (timer >= cooldown && playerWantToShoot);
            }

            bool playerWantToShoot = false;
    };
}
