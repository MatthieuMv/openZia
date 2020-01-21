/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context 
*/

#include <criterion/criterion.h>

#include <openZia/Context.hpp>

using namespace oZ;

Test(Context, Constant)
{
    Context context;

    cr_assert(context.isConstant());
    context.notConstant();
    cr_assert_not(context.isConstant());
}

Test(Context, States)
{
    Context context;

    cr_assert_eq(context.getState(), State::BeforeAnalyze); context.nextState();
    cr_assert_eq(context.getState(), State::Analyze);       context.nextState();
    cr_assert_eq(context.getState(), State::AfterAnalyze);  context.nextState();
    cr_assert_eq(context.getState(), State::BeforeParse);   context.nextState();
    cr_assert_eq(context.getState(), State::Parse);         context.nextState();
    cr_assert_eq(context.getState(), State::AfterParse);    context.nextState();
    cr_assert_eq(context.getState(), State::BeforeResponse);context.nextState();
    cr_assert_eq(context.getState(), State::Response);      context.nextState();
    cr_assert_eq(context.getState(), State::AfterResponse); context.nextState();
    cr_assert_eq(context.getState(), State::Completed);     context.nextState();
    cr_assert_eq(context.getState(), State::Completed);
    cr_assert(context.isCompleted());
    context.setErrorState();
    cr_assert_eq(context.getState(), State::Error);         context.nextState();
    cr_assert_eq(context.getState(), State::Error);
    cr_assert(context.hasError());
}

Test(Context, Basics)
{
    Endpoint end1("127.0.0.1", 4040), end2("192.127.4.1", 80);
    Context context(Buffer(), end1);
    const auto &ctx = context;

    cr_assert(context.getBuffer().empty());
    cr_assert(ctx.getBuffer().empty());
    cr_assert_eq(context.getEndpoint(), end1);
    context.setEndpoint(end2);
    cr_assert_eq(context.getEndpoint(), end2);
}