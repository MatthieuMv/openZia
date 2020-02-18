/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Request
*/

#include <criterion/criterion.h>

#include <openZia/RequestHTTP.hpp>

using namespace oZ::HTTP;

Test(Request, Basics)
{
    Request base;
    const auto &cbase(base);

    base.setMethod(Method::Get);
    base.getURI() = "index.html";
    base.getBody() = "hello";
    base.setVersion(Version(1, 1));
    cr_assert_eq(base.getMethod(), Method::Get);
    cr_assert_eq(base.getURI(), "index.html");
    cr_assert_eq(base.getBody(), "hello");
    cr_assert_eq(base.getVersion(), Version(1, 1));

    base.setMethod(Method::Post);
    base.getURI() = "azerty";
    base.setVersion(Version(1, 0));

    cr_assert_eq(base.getMethod(), Method::Post);
    cr_assert_eq(base.getURI(), "azerty");
    cr_assert_eq(base.getVersion(), Version(1, 0));

    cr_assert_not(base.getHeader().exists("abc"));

    base.getQueryParameters()["abc"] = "42";
    cr_assert_eq(base.getQueryParameters().at("abc"), "42");
}