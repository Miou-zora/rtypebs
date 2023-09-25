/*
** EPITECH PROJECT, 2023
** rtypebs
** File description:
** indexed_zipper_iterator
*/

#pragma once

#include <tuple>
#include <iterator>
#include <utility>

namespace containers
{
    template <class... Containers>
    class indexed_zipper;
}

template <class... Containers>
class indexed_zipper_iterator
{
    template <class Container>
    using iterator_t = decltype(std::declval<Container>().begin());
    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

public:
    using value_type = std::tuple<size_t, it_reference_t<Containers> &...>;
    using reference = value_type;
    using pointer = void;
    using difference_type = size_t;
    using iterator_category = std::input_iterator_tag;
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;
    // If we want indexed_zipper_iterator to be built by zipper only .
    friend containers::zipper<Containers...>;
    indexed_zipper_iterator(iterator_tuple const &it_tuple, size_t max)
    {
        this->_current = it_tuple;
        this->_max = max;
        this->_idx = 0;
        if (_idx < _max && !all_set(_seq))
        {
            incr_all(_seq);
        }
    }

public:
    indexed_zipper_iterator(indexed_zipper_iterator const &z)
    {
        this->_current = z._current;
        this->_max = z._max;
        this->_idx = z._idx;
    }
    indexed_zipper_iterator operator++()
    {
        incr_all(_seq);
        return (*this);
    }

    indexed_zipper_iterator &operator++(int)
    {
        indexed_zipper_iterator tmp(*this);
        incr_all(_seq);
        return (tmp);
    }

    value_type operator*()
    {
        return (to_value(_seq));
    }

    value_type operator->()
    {
        return (to_value(_seq));
    }
    friend bool operator==(indexed_zipper_iterator const &lhs, indexed_zipper_iterator const &rhs)
    {

        if (std::tie(lhs._current) != std::tie(rhs._current)) {
            return (false);
        }
        return (true);
    }
    friend bool operator!=(indexed_zipper_iterator const &lhs, indexed_zipper_iterator const &rhs)
    {
        return (!(lhs == rhs));
    }

private:
    // Increment every iterator at the same time . It also skips to the next value if one of the pointed to std ::optional does not contains a value.
    template <size_t... Is>
    void incr_all(std::index_sequence<Is...>)
    {
        do {
            (++std::get<Is>(_current), ...);
            _idx++;
        } while (_idx < _max && !all_set(_seq));
    }

    // check if every std :: optional are set .
    template <size_t... Is>
    bool all_set(std::index_sequence<Is...>)
    {
        return ((std::get<Is>(_current)->has_value() && ...));
    }

    // return a tuple of reference to components .
    template <size_t... Is>
    value_type to_value(std::index_sequence<Is...>)
    {
        return (std::tie(_idx, *std::get<Is>(_current)...));
    }

private:
    iterator_tuple _current;
    size_t _max; // compare this value to _idx to prevent infinite loop .
    size_t _idx;
    static constexpr std::index_sequence_for<Containers...> _seq{};
};
