/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Request
*/

#pragma once

#include "HeaderHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ { namespace HTTP { class Request; } }

class oZ::HTTP::Request
{
public:
    /**
     * @brief Construct a new Request object
     */
    Request(Method method = Method::NullMethod, URI &&uri = URI(), Version version = DefaultVersion)
        : _method(method), _uri(std::move(uri)), _version(version) {}

    /**
     * @brief Construct a new Request object by copy
     */
    Request(const Request &other) = default;

    /**
     * @brief Construct a new Request object by move
     */
    Request(Request &&other) = default;

    /**
     * @brief Destroy the Request object
     */
    ~Request(void) = default;

    /**
     * @brief Get request's method
     */
    [[nodiscard]] Method getMethod(void) const noexcept { return _method; }

    /**
     * @brief Set request's method
     */
    void setMethod(Method method) noexcept { _method = method; }

    /**
     * @brief Get request's URI reference
     */
    [[nodiscard]] URI &getURI(void) noexcept { return _uri; }

    /**
     * @brief Get request's URI constant reference
     */
    [[nodiscard]] const URI &getURI(void) const noexcept { return _uri; }

    /**
     * @brief Get request's version
     */
    [[nodiscard]] Version getVersion(void) const noexcept { return _version; }

    /**
     * @brief Set request's version
     */
    void setVersion(Version version) noexcept { _version = version; }

    /**
     * @brief Get the response's header reference
     */
    [[nodiscard]] Header &getHeader(void) noexcept { return _header; }

    /**
     * @brief Get the response's header constant reference
     */
    [[nodiscard]] const Header &getHeader(void) const noexcept { return _header; }

private:
    Method _method = Method::NullMethod;
    URI _uri;
    Version _version;
    Header _header;
};