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

    cr_assert_eq(context.getState(), State::BeforeParse);   context.nextState();
    cr_assert_eq(context.getState(), State::Parse);         context.nextState();
    cr_assert_eq(context.getState(), State::AfterParse);    context.nextState();
    cr_assert_eq(context.getState(), State::BeforeInterpret);context.nextState();
    cr_assert_eq(context.getState(), State::Interpret);      context.nextState();
    cr_assert_eq(context.getState(), State::AfterInterpret); context.nextState();
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
    Context context(Packet(ByteArray(), end1));
    const auto &ctx = context;

    cr_assert(context.getPacket().getByteArray().empty());
    cr_assert(ctx.getPacket().getByteArray().empty());
    cr_assert_eq(context.getPacket().getEndpoint(), end1);
    context.getPacket().setEndpoint(end2);
    cr_assert_eq(context.getPacket().getEndpoint(), end2);
    cr_assert_not(context.getPacket().hasEncryption());
    context.getPacket().setEncryption(true);
    cr_assert(context.getPacket().hasEncryption());
    cr_assert(ctx.getPacket().getFileDescriptor() == -1);
    context.getPacket().setFileDescriptor(42);
    cr_assert_eq(ctx.getPacket().getFileDescriptor(), 42);
}