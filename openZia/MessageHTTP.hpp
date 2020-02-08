/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: HTTP Message, base of requests and responses
 */

#pragma once

#include "HeaderHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ { namespace HTTP { class Message; } }

class oZ::HTTP::Message
{
public:
    /**
     * @brief Destroy the Message object
     */
    virtual ~Message(void) = default;

    /**
     * @brief Get the response's header reference
     */
    [[nodiscard]] Header &getHeader(void) noexcept { return _header; }

    /**
     * @brief Get the response's header constant reference
     */
    [[nodiscard]] const Header &getHeader(void) const noexcept { return _header; }

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
    void setVersion(const Version version) noexcept { _version = version; }

private:
    Header _header {};
    Body _body {};
    Version _version {};
};