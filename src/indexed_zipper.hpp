/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** indexed_zipper
*/

#pragma once

#include "indexed_zipper_iterator.hpp"

template <class... Containers>
class indexed_zipper
{
public:
    using iterator = indexed_zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;
    indexed_zipper(Containers &...cs)
    {
        _begin = iterator_tuple(cs.begin()...);
        _end = _compute_end(cs...);
        _size = _compute_size(cs...);
    }
    iterator begin()
    {
        return (iterator(_begin, _size));
    }

    iterator end()
    {
        return (iterator(_end, _size));
    }

private:
    // helper function to know the maximum index of our iterators .
    static size_t _compute_size(Containers &...containers)
    {
        return (std::min({containers.size()...}));
    }

    // helper function to compute an iterator_tuple that will allow us to build our end iterator.
    static iterator_tuple _compute_end(Containers &...containers)
    {
        size_t size = _compute_size(containers...);
        return (iterator_tuple((containers.begin() + size)...));
    }

private:
    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};
