/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Header 
*/

#include <criterion/criterion.h>

#include <openZia/HeaderHTTP.hpp>

#include "Utils.hpp"

using namespace oZ::HTTP;

Test(Header, Basics)
{
    Header header;
    const auto &hdr = header;

    cr_assert_not(header.valueExists("abc"));

    header.setValue("abc", "42");
    header.getValue("def") = "24";

    cr_assert_eq(header.getValue("abc"), "42");
    cr_assert_eq(hdr.getValue("def"), "24");

    cr_assert(CrashTest([&hdr] { const auto &var = hdr.getValue("azerty"); return var; }));
}