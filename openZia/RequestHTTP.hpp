/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Request
*/

#pragma once

#include "MessageHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ
{
    namespace HTTP
    {
        class Request;

        using QueryParameters = std::map<std::string, std::string, InsensitiveCompare>;
    }
}

class oZ::HTTP::Request : public Message
{
public:
    /**
     * @brief Destroy the Request object
     */
    ~Request(void) = default;

    /**
     * @brief Get request's URI reference
     */
    [[nodiscard]] inline URI &getURI(void) noexcept { return _uri; }

    /**
     * @brief Get request's URI constant reference
     */
    [[nodiscard]] inline const URI &getURI(void) const noexcept { return _uri; }

    /**
     * @brief Get request's QueryParameters reference
     */
    [[nodiscard]] inline QueryParameters &getQueryParameters(void) noexcept { return _queryParameters; }

    /**
     * @brief Get request's QueryParameters constant reference
     */
    [[nodiscard]] inline const QueryParameters &getQueryParameters(void) const noexcept { return _queryParameters; }

    /**
     * @brief Get request's method
     */
    [[nodiscard]] inline Method getMethod(void) const noexcept { return _method; }

    /**
     * @brief Set request's method
     */
    inline void setMethod(const Method method) noexcept { _method = method; }

private:
    URI _uri {};
    QueryParameters _queryParameters {};
    Method _method = Method::NullMethod;
};