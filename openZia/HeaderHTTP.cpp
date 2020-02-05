/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HeaderHTTP
*/

#include <stdexcept>

#include "HeaderHTTP.hpp"

using namespace oZ::HTTP;

const std::string &Header::get(const std::string &key) const
{
    if (auto it = _map.find(key); it == _map.end())
        throw std::logic_error("Header::get: '" + key + "' not found");
    return _map.at(key);
}