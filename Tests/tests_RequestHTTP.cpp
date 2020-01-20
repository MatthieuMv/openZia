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
    Request base(Method::Get, "index.html", Version(1, 1)), req(base);

    cr_assert_eq(req.getMethod(), Method::Get);
    cr_assert_eq(req.getURI(), "index.html");
    cr_assert_eq(req.getVersion(), Version(1, 1));

    req.setMethod(Method::Post);
    req.getURI() = "azerty";
    req.setVersion(Version(1, 0));

    cr_assert_eq(req.getMethod(), Method::Post);
    cr_assert_eq(req.getURI(), "azerty");
    cr_assert_eq(req.getVersion(), Version(1, 0));

    cr_assert_not(req.getHeader().exists("abc"));
}