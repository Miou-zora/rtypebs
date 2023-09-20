/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** zipper
*/

#ifndef ZIPPER_HPP_
#define ZIPPER_HPP_

#include "zipper_iterator.hpp"

template <class... Containers>
class zipper
{
public:
    using iterator = zipper_iterator<Containers...>;
    using iterator_tuple = typename iterator::iterator_tuple;
    zipper(Containers &...cs)
    {
        _begin = iterator_tuple(cs.begin()...);
        _end = iterator_tuple(cs.end()...);
        _size = _compute_size(cs...);
    }
    iterator begin()
    {
        return (iterator(_begin, _size));
    }

    iterator end()
    {
        return (iterator(_end, 0));
    }

private:
    // helper function to know the maximum index of our iterators .
    static size_t _compute_size(Containers &...containers);    // helper function to compute an iterator_tuple that will allow us to build our end iterator.static iterator_tuple _compute_end(Containers &...containers);

private:
    iterator_tuple _begin;
    iterator_tuple _end;
    size_t _size;
};

#endif /* !ZIPPER_HPP_ */
