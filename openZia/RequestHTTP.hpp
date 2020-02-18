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
    [[nodiscard]] URI &getURI(void) noexcept { return _uri; }

    /**
     * @brief Get request's URI constant reference
     */
    [[nodiscard]] const URI &getURI(void) const noexcept { return _uri; }

    /**
     * @brief Get request's QueryParameters reference
     */
    [[nodiscard]] QueryParameters &getQueryParameters(void) noexcept { return _queryParameters; }

    /**
     * @brief Get request's QueryParameters constant reference
     */
    [[nodiscard]] const QueryParameters &getQueryParameters(void) const noexcept { return _queryParameters; }


    /**
     * @brief Get request's method
     */
    [[nodiscard]] Method getMethod(void) const noexcept { return _method; }

    /**
     * @brief Set request's method
     */
    void setMethod(const Method method) noexcept { _method = method; }

private:
    URI _uri {};
    QueryParameters _queryParameters {};
    Method _method = Method::NullMethod;
};