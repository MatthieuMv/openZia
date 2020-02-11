/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** Endpoint
*/

#pragma once

#include <cstring>
#include <string>
#include <cinttypes>

namespace oZ
{
    class Endpoint;

    using IP = std::uint32_t;
    using Port = std::uint16_t;
    using FileDescriptor = std::int32_t;
}

class oZ::Endpoint
{
public:
    /**
     * @brief Construct a new Endpoint object
     */
    Endpoint(void) = default;

    /**
     * @brief Construct a new Endpoint object using IP as string
     */
    Endpoint(const std::string &ip, Port port) : _port(port) { setAddress(ip); }

    /**
     * @brief Construct a new Endpoint object using IP as 4 bytes value
     */
    Endpoint(IP ip, Port port) : _ip(ip), _port(port) {}

    /**
     * @brief Construct a new Endpoint object
     */
    Endpoint(const Endpoint &other) = default;

    /**
     * @brief Destroy the Endpoint objecti
     */
    ~Endpoint(void) = default;

    /**
     * @brief Copy operator
     */
    Endpoint &operator=(const Endpoint &other) = default;

    /**
     * @brief Equality operator
     */
    bool operator==(const Endpoint &other) const noexcept { return _ip == other._ip && _port == other._port; }

    /**
     * @brief Get internal address as formated string
     *
     * @return std::string IP Address formated as 'X.X.X.X'
     */
    std::string getAddress(void) const noexcept;

    /**
     * @brief Retreive internal ip in 4 bytes
     */
    IP getAddressValue(void) const noexcept { return _ip; }

    /**
     * @brief Set the Address object using a string
     */
    void setAddress(const std::string &ip);

    /**
     * @brief Set the Address object using a 4 byte value
     */
    void setAddress(const IP ip) { _ip = ip; }

    /**
     * @brief Get internal port
     */
    Port getPort(void) const noexcept { return _port; }

    /**
     * @brief Set internal port
     */
    void setPort(const Port port) noexcept { _port = port; }

private:
    IP _ip = 0;
    Port _port = 0;
};