/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include "sparse_array.hpp"
#include "entity_t.hpp"
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>

class registry
{
public:
    registry() {}
    ~registry() {}

    template <class Component>
    sparse_array<Component> &register_component()
    {
        _components[std::type_index(typeid(Component))] = std::make_pair(sparse_array<Component>(),
                                                                         [](registry &reg, entity_t const &entity)
                                                                         {
                                                                             sparse_array<Component> &arr = reg.get_components<Component>();
                                                                             arr.erase(entity);
                                                                         });
        return (std::any_cast<sparse_array<Component> &>(_components[std::type_index(typeid(Component))].first));
    }

    template <class Component>
    sparse_array<Component> &get_components()
    {
        return (std::any_cast<sparse_array<Component> &>(_components[std::type_index(typeid(Component))].first));
    }

    template <class Component>
    sparse_array<Component> const &get_components() const
    {
        return (std::any_cast<sparse_array<Component> const &>(_components.at(std::type_index(typeid(Component))).first));
    }

    entity_t spawn_entity()
    {
        static int id = 0;

        if (_dead_entities.empty())
        {
            return (entity_t(id++));
        }

        entity_t e = _dead_entities.back();
        _dead_entities.pop_back();
        return (e);
    }

    entity_t entity_from_index(std::size_t idx)
    {
        return (entity_t(idx));
    }

    void kill_entity(entity_t const &e)
    {
        for (auto &component : _components)
        {
            component.second.second(*this, e);
        }
        _dead_entities.push_back(e);
    }

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(entity_t const &to,
                                                                   Component &&c)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.insert_at(to, std::forward<Component>(c));
        return (arr[to]);
    }

    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&...p)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.emplace_at(to, std::forward<Params>(p)...);
        return (arr[to]);
    }

    template <typename Component>
    void remove_component(entity_t const &from)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.erase(from);
    }

    template <class... Components, typename Function>
    void add_system(Function &&f)
    {
        _systems.push_back([f](registry &reg)
                           { f(reg, reg.get_components<Components>()...); });
    }
    // or
    template <class... Components, typename Function>
    void add_system(Function const &f)
    {
        _systems.push_back([f](registry &reg)
                           { f(reg, reg.get_components<Components>()...); });
    }

    void run_systems()
    {
        for (auto &system : _systems)
        {
            system(*this);
        }
    }

private:
    std::unordered_map<std::type_index, std::pair<std::any, std::function<void(registry &, entity_t const &)>>> _components; // TODO: switch from pair to class
    std::vector<std::function<void(registry &)>> _systems;
    std::vector<entity_t> _dead_entities;
};

#endif /* !REGISTRY_HPP_ */
