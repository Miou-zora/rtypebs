/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** shooter
*/

#pragma once

#include "prefab.hpp"

namespace component
{
    class   shooter {
        public:
            shooter(const std::string &projectileName_, float _cooldown = 0.5) : cooldown(_cooldown), projectileName(projectileName_) {};
            float cooldown;
            float timer = 0;
            std::string projectileName;

            virtual void update(float deltaTime)
            {
                timer += deltaTime;
            }

            virtual void reset(void)
            {
                timer = 0;
            }

            virtual bool canShoot(void)
            {
                return (timer >= cooldown);
            }
    };
};
