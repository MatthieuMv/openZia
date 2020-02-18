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
    header.set("def", "24");

    cr_assert_eq(header.get("abc"), "42");
    cr_assert_eq(hdr.get("def"), "24");

    cr_assert(CrashTest([&hdr] { const auto &var = hdr.get("azerty"); return var; }));
}

Test(Header, Advanced)
{
    Header header;
    const auto &cheader = header;
    std::string x = "x";

    cr_assert_eq(header.count(x), 0);
    header.set("x", "1");
    cr_assert_eq(header.count(x), 1);
    header.set(x, "2");
    cr_assert_eq(header.count(x), header.getStringMultimap().count(x));
    cr_assert_eq(header.get("x", 0), "1");
    cr_assert_eq(header.get(x, 1), "2");

    auto it = header.getIterator("x");
    cr_assert_eq(it->second, "1");
    ++it;
    cr_assert_eq(it->second, "2");

    auto cit = cheader.getIterator("x");
    cr_assert_eq(cit->second, "1");
    ++cit;
    cr_assert_eq(cit->second, "2");

    auto range = header.getIteratorRange("x");
    cr_assert_eq(std::distance(range.first, range.second), 2);
    auto crange = cheader.getIteratorRange(x);
    cr_assert_eq(std::distance(crange.first, crange.second), 2);
}

Test(Header, Error)
{
    Header header;
    const Header &cheader = header;

    CrashTest([&cheader] { return cheader.get("x", 0); });
    header.set("x", "1");
    CrashTest([&header] { return header.get("x", 1); });
}