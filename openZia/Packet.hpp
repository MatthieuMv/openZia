/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** NetworkPacket
*/

#pragma once

#include "ByteArray.hpp"
#include "Endpoint.hpp"

namespace oZ { class Packet; }

class oZ::Packet
{
public:
    /**
     * @brief Construct a new Packet object
     */
    Packet(void) = default;

    /**
     * @brief Construct a new Packet object using byteArray and an endpoint
     */
    Packet(ByteArray &&byteArray, const Endpoint endpoint) : _byteArray(std::move(byteArray)), _endpoint(endpoint) {}

    /**
     * @brief Destroy the Packet object
     */
    ~Packet(void) = default;

    /**
     * @brief Get the ByteArray of the context
     */
    [[nodiscard]] ByteArray &getByteArray(void) noexcept { return _byteArray; }

    /**
     * @brief Get the ByteArray of the context (constant)
     */
    [[nodiscard]] const ByteArray getByteArray(void) const noexcept { return _byteArray; }

    /**
     * @brief Get the current context' state
     */
    [[nodiscard]] Endpoint getEndpoint(void) const noexcept { return _endpoint; }

    /**
     * @brief Set the Endpoint target
     */
    void setEndpoint(Endpoint endpoint) noexcept { _endpoint = endpoint; }

    /**
     * @brief Get the Encryption Key
     */
    [[nodiscard]] std::string &getEncryptionKey(void) noexcept { return _encryptionKey; }

    /**
     * @brief Get the Encryption Key (constant)
     */
    [[nodiscard]] const std::string &getEncryptionKey(void) const noexcept { return _encryptionKey; }

    /**
     * @brief Check the usage of encryption port (default HTTPS is 443)
     */
    [[nodiscard]] bool hasEncryption(void) const noexcept { return _useEncryption; }

    /**
     * @brief Set the encryption state
     */
    void setEncryption(bool value) noexcept { _useEncryption = value; }

private:
    ByteArray _byteArray;
    Endpoint _endpoint;
    std::string _encryptionKey;
    bool _useEncryption = false;
};