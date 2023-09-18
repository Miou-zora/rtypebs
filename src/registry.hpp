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

    template <class Component>
    sparse_array<Component> &register_component()
    {
        _components[std::type_index(typeid(Component))] = std::make_pair(sparse_array<Component>(),
            [](registry &reg, entity_t const &entity)
        {
            sparse_array<Component> &arr = reg.get_components<Component>();
            arr.erase(entity.id());
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
        return (entity_t(id++));
    }

    entity_t entity_from_index(std::size_t idx)
    {
        return (entity_t(idx));
    }

    void kill_entity(entity_t const &e)
    {
        for (auto &component : _components) {
            component.second.second(*this, e);
        }
    }

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(entity_t const &to,
                                                                   Component &&c)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.insert_at(to.id(), std::forward<Component>(c));
        return (arr[to.id()]);
    }
    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&...p)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.emplace(to.id(), std::forward<Params>(p)...);
        return (arr[to.id()]);
    }

    template <typename Component>
    void remove_component(entity_t const &from)
    {
        sparse_array<Component> &arr = get_components<Component>();
        arr.erase(from.id());
    }

private:
    std::unordered_map<std::type_index, std::pair<std::any, std::function<void(registry &, entity_t const &)>>> _components;
};


#endif /* !REGISTRY_HPP_ */
