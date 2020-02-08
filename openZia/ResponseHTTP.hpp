/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Response
*/

#pragma once

#include "MessageHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ { namespace HTTP { class Response; } }

/**
 * @brief The HTTP response inherits from the header
 */
class oZ::HTTP::Response : public Message
{
public:
    /**
     * @brief Destroy the Response object
     */
    virtual ~Response(void) = default;

    /**
     * @brief Get request's code
     */
    [[nodiscard]] Code getCode(void) const noexcept { return _code; }

    /**
     * @brief Set request's code
     */
    void setCode(const Code code) noexcept { _code = code; }

    /**
     * @brief Get request's Reason reference
     */
    [[nodiscard]] Reason &getReason(void) noexcept { return _reason; }

    /**
     * @brief Get request's Reason constant reference
     */
    [[nodiscard]] const Reason &getReason(void) const noexcept { return _reason; }

private:
    Reason _reason {};
    Code _code = Code::Undefined;
};