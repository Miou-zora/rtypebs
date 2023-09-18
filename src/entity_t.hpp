/*
** EPITECH PROJECT, 2023
** B-CPP-500-NAN-5-1-bsrtype-alexandre.franquet
** File description:
** entity_t
*/

#ifndef ENTITY_T_HPP_
#define ENTITY_T_HPP_

#include <cstddef>

class entity_t
{
public:
    explicit entity_t(std::size_t id) : _id(id){};

    std::size_t id() const
    {
        return (_id);
    }

private:
    std::size_t _id;
};

#endif /* !ENTITY_T_HPP_ */
