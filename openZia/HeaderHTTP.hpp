/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HeaderHTTP
*/

#pragma once

#include <unordered_map>

#include "BaseHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ { namespace HTTP { class Header; } }

/**
 * @brief The HTTP Header is a simple map of string used to store header values
 */
class oZ::HTTP::Header
{
public:
    /**
     * @brief Check existence of a value in the header
     */
    [[nodiscard]] bool exists(const std::string &key) const noexcept { return _map.find(key) != _map.end(); }

    /**
     * @brief Get a value in the header, and insert it if not found
     */
    [[nodiscard]] std::string &get(const std::string &key) { return _map[key]; }

    /**
     * @brief Get a value in the header, and throw if not found
     */
    [[nodiscard]] const std::string &get(const std::string &key) const;

    /**
     * @brief Get a value in the header
     */
    template<typename Literal>
    void set(const std::string &key, Literal &&value) { get(key) = std::forward<Literal>(value); }

private:
    std::unordered_map<std::string, std::string> _map {};
};
