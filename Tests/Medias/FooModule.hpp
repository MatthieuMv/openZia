/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** FooModule
*/

#pragma once

#include <openZia/IModule.hpp>

class FooModule : public oZ::IModule
{
public:
    virtual const char *getName(void) const { return "Foo"; }
    virtual void onRegisterCallbacks(oZ::Pipeline &) {}
};