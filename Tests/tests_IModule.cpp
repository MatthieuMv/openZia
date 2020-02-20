/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module Interface
*/

#include <criterion/criterion.h>

#include <openZia/IModule.hpp>

class Test : public oZ::IModule
{
public:
    virtual const char *getName(void) const { return "Test"; }
    virtual void onRegisterCallbacks(oZ::Pipeline &) {}
};

Test(IModule, Basics)
{
    Test module;

    cr_assert_str_eq(module.getName(), "Test");
    cr_assert_eq(module.getDependencies(), oZ::IModule::Dependencies());
}