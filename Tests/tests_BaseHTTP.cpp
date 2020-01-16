/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HTTP Abstraction Base 
*/

#include <criterion/criterion.h>

#include <openZia/BaseHTTP.hpp>

using namespace oZ::HTTP;

/**
 * @brief Assert that we can cast the code to its actual scalar type.
 * 
 *  This is needed to convert the Code enum-class to an actual http code 
 */
Test(BaseHTTP, Code)
{
    cr_assert_eq(static_cast<int>(Code::Undefined), 0);
    cr_assert_eq(static_cast<int>(Code::OK), 200);
}

/**
 * @brief Check the HTTP methods names of version 1.1
 */
Test(BaseHTTP, Method)
{
    cr_assert_str_eq(MethodName(Method::Option),    "OPTION");
    cr_assert_str_eq(MethodName(Method::Get),       "GET");
    cr_assert_str_eq(MethodName(Method::Head),      "HEAD");
    cr_assert_str_eq(MethodName(Method::Post),      "POST");
    cr_assert_str_eq(MethodName(Method::Put),       "PUT");
    cr_assert_str_eq(MethodName(Method::Delete),    "DELETE");
    cr_assert_str_eq(MethodName(Method::Trace),     "TRACE");
    cr_assert_str_eq(MethodName(Method::Connect),   "CONNECT");
}