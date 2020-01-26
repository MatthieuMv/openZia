/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Response
*/

#pragma once

#include "HeaderHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ { namespace HTTP { class Response; } }

/**
 * @brief The HTTP response inherits from the header
 */
class oZ::HTTP::Response
{
public:
    /**
     * @brief Construct a new Response object
     */
    Response(Code code = Code::Undefined, Reason &&reason = Reason(), Body &&body = Body(), Version version = DefaultVersion)
        : _code(code), _reason(std::move(reason)), _body(std::move(body)), _version(version) {}

    /**
     * @brief Construct a new Response object by copy
     */
    Response(const Response &other) = default;

    /**
     * @brief Construct a new Response object by move
     */
    Response(Response &&other) = default;

    /**
     * @brief Destroy the Response object
     */
    ~Response(void) = default;

    /**
     * @brief Get request's code
     */
    [[nodiscard]] Code getCode(void) const noexcept { return _code; }

    /**
     * @brief Set request's code
     */
    void setCode(Code code) noexcept { _code = code; }

    /**
     * @brief Get request's Reason reference
     */
    [[nodiscard]] Reason &getReason(void) noexcept { return _reason; }

    /**
     * @brief Get request's Reason constant reference
     */
    [[nodiscard]] const Reason &getReason(void) const noexcept { return _reason; }

    /**
     * @brief Get request's Body reference
     */
    [[nodiscard]] Body &getBody(void) noexcept { return _body; }

    /**
     * @brief Get request's Body constant reference
     */
    [[nodiscard]] const Body &getBody(void) const noexcept { return _body; }

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
    Code _code = Code::Undefined;
    Reason _reason;
    Body _body;
    Version _version;
    Header _header;
};