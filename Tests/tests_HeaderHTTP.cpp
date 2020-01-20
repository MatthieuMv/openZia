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

    cr_assert_not(header.exists("abc"));

    header.set("abc", "42");
    header.get("def") = "24";

    cr_assert_eq(header.get("abc"), "42");
    cr_assert_eq(hdr.get("def"), "24");

    cr_assert(CrashTest([&hdr] { const auto &var = hdr.get("azerty"); return var; }));
}