/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Network Endpoint
*/

#include <arpa/inet.h>

#include <criterion/criterion.h>

#include <openZia/Endpoint.hpp>

#include "Utils.hpp"

using namespace oZ;

Test(Endpoint, Basics)
{
    Endpoint end1, end2("127.0.0.1", 4040), end3(0, 80), end4(end2);

    cr_assert_eq(end1.getAddressValue(), 0);
    cr_assert_eq(end1.getAddress(), "0.0.0.0");
    cr_assert_eq(end1.getPort(), 0);

    cr_assert_eq(end2.getAddressValue(), ::inet_addr("127.0.0.1"));
    cr_assert_eq(end2.getAddress(), "127.0.0.1");
    cr_assert_eq(end2.getPort(), 4040);

    cr_assert_eq(end3.getAddressValue(), 0);
    cr_assert_eq(end3.getAddress(), "0.0.0.0");
    cr_assert_eq(end3.getPort(), 80);

    cr_assert_eq(end4.getAddressValue(), end2.getAddressValue());
    cr_assert_eq(end4.getAddress(), end2.getAddress());
    cr_assert_eq(end4.getPort(), end2.getPort());
}

Test(Endpoint, Errors)
{
    cr_assert(CrashTest([]{ Endpoint("127.0", 0); }));
    cr_assert(CrashTest([]{ Endpoint("127.0.1", 0); }));
    cr_assert(CrashTest([]{ Endpoint("127.0.0.1.2", 0); }));
    cr_assert(CrashTest([]{ Endpoint("127.0.O.1", 0); }));
    cr_assert(CrashTest([]{ Endpoint("", 0); }));
    cr_assert(CrashTest([]{ Endpoint("aze", 0); }));
    cr_assert(CrashTest([]{ Endpoint("a.b.c.d", 0); }));
    cr_assert(CrashTest([]{ Endpoint("...", 0); }));
    cr_assert(CrashTest([]{ Endpoint("0.0.0.", 0); }));
    cr_assert(CrashTest([]{ Endpoint(".0.0.0", 0); }));
}