/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Response
*/

#include <criterion/criterion.h>

#include <openZia/ResponseHTTP.hpp>

using namespace oZ::HTTP;

Test(Response, Basics)
{
    Response base;

    base.setCode(Code::OK);
    base.getReason() = "all is";
    base.getBody() = "hello";
    base.setVersion(Version(1, 1));
    cr_assert_eq(base.getCode(), Code::OK);
    cr_assert_eq(base.getReason(), "all is");
    cr_assert_eq(base.getBody(), "hello");
    cr_assert_eq(base.getVersion(), Version(1, 1));

    base.setCode(Code::Accepted);
    base.getReason() = "good";
    base.getBody() = "world";
    base.setVersion(Version(1, 0));
    cr_assert_eq(base.getCode(), Code::Accepted);
    cr_assert_eq(base.getReason(), "good");
    cr_assert_eq(base.getBody(), "world");
    cr_assert_eq(base.getVersion(), Version(1, 0));

    cr_assert_not(base.getHeader().exists("abc"));
}