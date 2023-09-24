/*
** EPITECH PROJECT, 2023
** rtypebs [WSL : Ubuntu]
** File description:
** prefab
*/

#pragma once

#include <unordered_map>
#include <any>
#include <vector>
#include <typeindex>
#include "registry.hpp"
#include "displayable_hurtbox.hpp"

template <class... Components>
class prefab
{
    public:
        prefab()
        {
            (add_component<Components>(), ...);
        }
        virtual ~prefab() = default;

        template <class Component, typename... Args>
        prefab &add_component(Args... args)
        {
            _components[std::type_index(typeid(Component))] = (std::make_any<Component>(args...));
            return (*this);
        }

        entity_t instantiate(registry &reg)
        {
            entity_t entity = reg.spawn_entity();

            (reg.add_component<Components>(entity, std::any_cast<Components>(_components[std::type_index(typeid(Components))])), ...);
            return (entity);
        }

    private:
        std::unordered_map<std::type_index, std::any> _components;

};
