/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** entity_t
*/

#pragma once

#include <cstddef>

class entity_t
{
public:
    explicit entity_t(std::size_t id) : _id(id){};

    operator std::size_t() const
    {
        return (_id);
    }

private:
    std::size_t _id;
};
