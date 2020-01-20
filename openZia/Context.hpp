/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#pragma once

#include "HTTP.hpp"
#include "Endpoint.hpp"

namespace oZ
{
    enum State : std::uint8_t {
        // An error occured and the pipeline musn't continue its processing
        Error = 0,

        // Analyze callbacks are used to preprocess a HTTP request
        BeforeAnalyze,
        Analyze,
        AfterAnalyze,

        // Parse callbacks are used to process a HTTP request
        BeforeParse,
        Parse,
        AfterParse,

        // Response callbacks are used to create a HTTP response
        BeforeResponse,
        Response,
        AfterResponse,

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
 */
class oZ::Context
{
public:
    /**
     * @brief Construct a new Context object
     */
    Context(void) = default;

    /**
     * @brief Construct a new Context object by copy
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
     * @brief Get the Request of the HTTP context
     */
    [[nodiscard]] HTTP::Request getRequest(void) noexcept { return _request; }

    /**
     * @brief Get the Request of the HTTP context (constant)
     */
    [[nodiscard]] const HTTP::Request getRequest(void) const noexcept { return _request; }

    /**
     * @brief Get the Response of the HTTP context
     */
    [[nodiscard]] HTTP::Response getResponse(void) noexcept { return _response; }

    /**
     * @brief Get the Response of the HTTP context (constant)
     */
    [[nodiscard]] const HTTP::Response getResponse(void) const noexcept { return _response; }

    /**
     * @brief Get the current context' state
     */
    [[nodiscard]] Endpoint getEndpoint(void) const noexcept { return _endpoint; }

    /**
     * @brief Set the Endpoint target
     */
    void setEndpoint(Endpoint endpoint) noexcept { _endpoint = endpoint; }

    /**
     * @brief Get the current context' state
     */
    [[nodiscard]] State getState(void) const noexcept { return _state; }

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

private:
    HTTP::Request _request;
    HTTP::Response _response;
    Endpoint _endpoint;
    State _state = State::BeforeAnalyze;
    bool _constant = true;
};