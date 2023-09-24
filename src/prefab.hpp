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

class prefab
{
    public:
        prefab() = default;
        virtual ~prefab() = default;

        template <class Component, typename... Args>
        prefab &add_component(Args... args)
        {
            _components[std::type_index(typeid(Component))] = ([args...](registry &reg, const entity_t &entity) -> void {
                reg.add_component<Component>(entity, Component(args...));
            });
            return (*this);
        }

        entity_t instantiate(registry &reg)
        {
            entity_t entity = reg.spawn_entity();

            for (auto &component : _components) {
                component.second(reg, entity);
            }
            return (entity);
        }

    private:
        std::unordered_map<std::type_index, std::function<void(registry &, const entity_t &)>> _components;

};
