/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Endpoint
*/

#include <stdexcept>

#include "Endpoint.hpp"

using namespace oZ;

std::string Endpoint::getAddress(void) const noexcept
{
    auto *ptr = reinterpret_cast<const std::uint8_t *>(&_ip);
    std::string res;

    for (auto i = 0; i < 4; ++i) {
        if (i)
            res.push_back('.');
        res += std::to_string(static_cast<unsigned>(ptr[i]));
    }
    return res;
}

void Endpoint::setAddress(const std::string &ip)
{
    try {
        auto *ptr = reinterpret_cast<std::uint8_t *>(&_ip);
        std::string cache;
        auto i = 0;

        for (auto c : ip) {
            if (c == '.') {
                ptr[i++] = static_cast<std::uint8_t>(std::stoul(cache));
                cache.clear();
            } else
                cache.push_back(c);
        }
        ptr[i++] = static_cast<std::uint8_t>(std::stoul(cache));
        cache.clear();
        if (i != 4)
            throw std::logic_error(nullptr);
    } catch (...) {
        throw std::logic_error("Endpoint::setAddress: Invalid IP address '" + ip + "'");
    }
}
