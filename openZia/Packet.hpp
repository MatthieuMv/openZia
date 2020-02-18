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
    Packet(ByteArray &&byteArray, const Endpoint endpoint, const FileDescriptor fd = -1)
        : _byteArray(std::move(byteArray)), _endpoint(endpoint), _fd(fd) {}

    /**
     * @brief Destroy the Packet object
     */
    ~Packet(void) = default;

    /**
     * @brief Get the ByteArray of the context
     */
    [[nodiscard]] inline ByteArray &getByteArray(void) noexcept { return _byteArray; }

    /**
     * @brief Get the ByteArray of the context (constant)
     */
    [[nodiscard]] inline const ByteArray getByteArray(void) const noexcept { return _byteArray; }

    /**
     * @brief Get the current context's endpoint
     */
    [[nodiscard]] inline Endpoint getEndpoint(void) const noexcept { return _endpoint; }

    /**
     * @brief Set the Endpoint target
     */
    inline void setEndpoint(const Endpoint endpoint) noexcept { _endpoint = endpoint; }

    /**
     * @brief Get the context's file descriptor
     */
    [[nodiscard]] inline FileDescriptor getFileDescriptor(void) const noexcept { return _fd; }

    /**
     * @brief Set the context's file descriptor
     */
    inline void setFileDescriptor(const FileDescriptor fd) noexcept { _fd = fd; }

    /**
     * @brief Check the usage of encryption port (used for HTTPS)
     */
    [[nodiscard]] inline bool hasEncryption(void) const noexcept { return _useEncryption; }

    /**
     * @brief Set the encryption state
     */
    inline void setEncryption(const bool value) noexcept { _useEncryption = value; }

private:
    ByteArray _byteArray {};
    Endpoint _endpoint {};
    FileDescriptor _fd { -1 };
    bool _useEncryption = false;
};