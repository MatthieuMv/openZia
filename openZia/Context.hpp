/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#pragma once

#include <any>
#include <unordered_map>
#include <string>

#include "Packet.hpp"
#include "HTTP.hpp"

namespace oZ
{
    /**
     * @brief Context pipelines callbacks
     *
     *  This enum represent states of the pipeline' state pattern.
     */
    enum State : std::uint8_t {
        // Callback triggered when an error occured and the pipeline is stopping
        Error = 0,

        // Parse callbacks are used to parse HTTP requests
        BeforeParse,
        Parse,
        AfterParse,

        // Interpret callbacks are used to create HTTP responses
        BeforeInterpret,
        Interpret,
        AfterInterpret,

        // Callback when the pipeline is fully completed without errors
        Completed,

        StateCount
    };

    class Pipeline;

    class Context;
}

/**
 * @brief The context class uses different concepts :
 * 1) State is a state-machine code which indicates where the context
 * 2) Constant property should be set when an IModule want to specify that his process
 *    is constant and thus can be cached.
 * 3) Endpoint is the client who sent a message
 *
 *  Please notice that this class is intended to be reused (1 for each client) to store once its data and metadata
 */
class oZ::Context
{
public:
    /**
     * @brief Map containing implementation-dependant metadatas
     */
    using MetadataMap = std::unordered_map<std::string, std::any>;

    /**
     * @brief Construct a new Context object
     */
    Context(void) = default;

    /**
     * @brief Construct a new Context object using a packet
     */
    Context(Packet &&packet);

    /**
     * @brief Construct a new Context object by copy (this operation can be very expensive !!)
     */
    Context(const Context &other) = default;

    /**
     * @brief Construct a new Context object by move
     */
    Context(Context &&other) = default;

    /**
     * @brief Destroy the Context object
     */
    ~Context(void) = default;

    /**
     * @brief Get the network Packet of the context
     */
    [[nodiscard]] Packet &getPacket(void) noexcept { return _packet; }

    /**
     * @brief Get the network Packet of the context (constant)
     */
    [[nodiscard]] const Packet &getPacket(void) const noexcept { return _packet; }

    /**
     * @brief Get the Request of the HTTP context
     */
    [[nodiscard]] HTTP::Request &getRequest(void) noexcept { return _request; }

    /**
     * @brief Get the Request of the HTTP context (constant)
     */
    [[nodiscard]] const HTTP::Request &getRequest(void) const noexcept { return _request; }

    /**
     * @brief Get the Response of the HTTP context
     */
    [[nodiscard]] HTTP::Response &getResponse(void) noexcept { return _response; }

    /**
     * @brief Get the Response of the HTTP context (constant)
     */
    [[nodiscard]] const HTTP::Response &getResponse(void) const noexcept { return _response; }

    /**
     * @brief Get the current context' state
     */
    [[nodiscard]] State getState(void) const noexcept { return _state; }

    /**
     * @brief Set the current context' state
     */
    void setState(const State state) noexcept { _state = state; }

    /**
     * @brief Set internal state to the next one
     *  Return true if the state has changed (and the current state is neither Error nor Completed)
     */
    bool nextState(void) noexcept;

    /**
     * @brief Set nternal state to Error
     */
    void setErrorState(void) { _state = State::Error; }

    /**
     * @brief Fast error check
     */
    [[nodiscard]] bool hasError(void) const noexcept { return getState() == State::Error; }

    /**
     * @brief Fast completion check
     */
    [[nodiscard]] bool isCompleted(void) const noexcept { return getState() == State::Completed; }

    /**
     * @brief Tell that the Context is not constant and thus can't be cached
     */
    void notConstant(void) noexcept { _constant = false; }

    /**
     * @brief Check if the current Context's state is constant (and if it can be cached)
     */
    [[nodiscard]] bool isConstant(void) const noexcept { return _constant; }

    /**
     * @brief This function sets a metadata to be used by any module
     */
    template<typename Type>
    void setMetadata(const std::string &key, Type value);

    /**
     * @brief This function remove a metadata (if present)
     */
    void removeMetadata(const std::string &key);

    /**
     * @brief This function retreives a metadata to be used by any module
     */
    template<typename Type>
    Type &getMetadata(const std::string &key);

    /**
     * @brief This function retreives a metadata to be used by any module
     */
    template<typename Type>
    const Type &getMetadata(const std::string &key) const;

    /**
     * @brief This function checks if a metadata exist
     */
    bool hasMetadata(const std::string &key) const;

    /**
     * @brief Prepare the context to be used again with the same client
     */
    void clear(void);

private:
    Packet _packet {};
    HTTP::Request _request {};
    HTTP::Response _response {};
    State _state = State::BeforeParse;
    bool _constant = true;
    MetadataMap _metadata {};
};

#include "Context.ipp"
