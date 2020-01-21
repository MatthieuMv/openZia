/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#include "Context.hpp"
#include "Pipeline.hpp"

using namespace oZ;

Context::Context(Buffer &&buffer, const Endpoint endpoint)
    : _buffer(std::move(buffer)), _endpoint(endpoint)
{
}

bool Context::nextState(void) noexcept
{
    switch (getState()) {
    case State::Error:
    case State::Completed:
    case State::StateCount:
        return false;
    default:
        setState(static_cast<State>(static_cast<int>(getState()) + 1));
        return true;
    }
}