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
    Response base(Code::OK, "all is", "hello", Version(1, 1)), res(base);

    cr_assert_eq(res.getCode(), Code::OK);
    cr_assert_eq(res.getReason(), "all is");
    cr_assert_eq(res.getBody(), "hello");
    cr_assert_eq(res.getVersion(), Version(1, 1));

    res.setCode(Code::Accepted);
    res.getReason() = "good";
    res.getBody() = "world";
    res.setVersion(Version(1, 0));

    cr_assert_eq(res.getCode(), Code::Accepted);
    cr_assert_eq(res.getReason(), "good");
    cr_assert_eq(res.getBody(), "world");
    cr_assert_eq(res.getVersion(), Version(1, 0));

    cr_assert_not(res.getHeader().exists("abc"));
}