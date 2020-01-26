/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** FooModule
*/

#include "FooModule.hpp"

extern "C" oZ::ModulePtr CreateModule(void) { return std::make_shared<FooModule>(); }