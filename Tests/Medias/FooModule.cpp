/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** FooModule
*/

#include "FooModule.hpp"

extern "C" oZ::IModule *CreateModule(void) { return new FooModule(); }