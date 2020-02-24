/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#include "Context.hpp"
#include "Pipeline.hpp"

using namespace oZ;

Context::Context(Packet &&packet)
    : _packet(std::move(packet))
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

void Context::removeMetadata(const std::string &key)
{
    const auto &it = _metadata.find(key);

    if (it != _metadata.end())
        _metadata.erase(it);
}

bool Context::hasMetadata(const std::string &key) const
{
    return _metadata.find(key) != _metadata.end();
}

void Context::clear(void)
{
    _packet.clear();
    _request.clear();
    _response.clear();
    _state = State::BeforeParse;
    _constant = true;
}