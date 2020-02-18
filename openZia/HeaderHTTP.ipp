/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HeaderHTTP
*/

#include <stdexcept>

template<typename Literal>
std::string &oZ::HTTP::Header::get(const Literal &key, const std::uint32_t index)
{
    auto range = getIteratorRange(key);

    if (auto dist = std::distance(range.first, range.second); !dist || index >= dist)
        throw std::out_of_range(std::string("Header::get: '") + key + "' with index '" + std::to_string(dist) + "' not found");
    std::advance(range.first, index);
    return range.first->second;
}

template<typename Literal>
const std::string &oZ::HTTP::Header::get(const Literal &key, const std::uint32_t index) const
{
    auto range = getIteratorRange(key);

    if (auto dist = std::distance(range.first, range.second); !dist || index >= dist)
        throw std::out_of_range(std::string("Header::get: '") + key + "' with index '" + std::to_string(dist) + "' not found");
    std::advance(range.first, index);
    return range.first->second;
}