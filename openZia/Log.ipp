/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** Log
*/

#pragma once

#include <iostream>

template<typename Type>
oZ::Log &oZ::Log::operator<<(Type &&value)
{
    _os << std::forward<Type>(value);
    return *this;
}
