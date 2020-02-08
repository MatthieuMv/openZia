/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** tests_DynamicLoader
*/

#include <criterion/criterion.h>
#include <openZia/OperatingSystem.hpp>
#include <openZia/DynamicLoader.hpp>
#include <openZia/IModule.hpp>

#include "Utils.hpp"

#if defined(SYSTEM_LINUX)
    static const std::string Extension = ".so";
#elif defined(SYSTEM_WINDOWS)
    static const std::string Extension = ".dll";
#endif

Test(DynamicLoader, Basics)
{
    oZ::DynamicLoader loader;

    auto handler = loader.load("./libFoo" + Extension);
    cr_assert(handler);

    auto function = loader.getFunction<oZ::ModuleInstanceFunction>(handler, "CreateModule");
    cr_assert(function);

    oZ::ModulePtr module { (*function)() };
    cr_assert(module.get());
    cr_assert_str_eq(module->getName(), "Foo");

    // Must destroy the module before closing the handle, if not it can't resolve virtual destructor
    module.reset();
    loader.release();
}

Test(DynamicLoader, Errors)
{
    oZ::DynamicLoader loader;

    cr_assert_eq(loader.getHandlerPath(nullptr), std::string());

    cr_assert(CrashTest([&loader]{ return loader.load("./azerty/uiop" + Extension); }));

    auto handler = loader.load("./libFoo" + Extension);
    cr_assert(handler);

    cr_assert(CrashTest([&loader, handler]{ return loader.getFunction(handler, "azerty"); }));
}