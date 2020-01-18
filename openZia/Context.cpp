/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context
*/

#include "Context.hpp"
#include "APipeline.hpp"

using namespace oZ;

void Context::nextState(void) noexcept
{
    switch (_state) {
    case State::Error:
    case State::Completed:
    case State::StateCount:
        break;
    default:
        _state = static_cast<State>(static_cast<int>(_state) + 1);
        break;
    }
}