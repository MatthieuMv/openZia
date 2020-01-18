/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Utils
*/

#pragma once

/**
 * @brief Returns true if callback crashed
 */
template<typename T>
bool CrashTest(T &&function)
{
    try {
        function();
        return false;
    } catch (...) {
        return true;
    }
}
