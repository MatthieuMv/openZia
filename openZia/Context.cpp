/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#include "Context.hpp"
#include "Pipeline.hpp"

using namespace oZ;

bool Context::nextState(void) noexcept
{
    switch (_state) {
    case State::Error:
    case State::Completed:
    case State::StateCount:
        return false;
    default:
        _state = static_cast<State>(static_cast<int>(_state) + 1);
        return true;
    }
}