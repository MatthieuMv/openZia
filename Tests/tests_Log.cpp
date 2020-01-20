/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** Log
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <openZia/Log.hpp>

using namespace oZ;

Test(Log, StdOut, .init=cr_redirect_stdout)
{
    oZ::Log() << "Hello world " << 42;
    cr_stdout_match_str("Hello world 42\n");
}

class TestLogger : public ILogger
{
public:
    TestLogger(std::string &content) : _content(content) {}
    virtual ~TestLogger(void) = default;

    virtual void onLog(Level, const std::string &message) {
        _content += message;
        _content += '\n';
    }

    virtual const char *getName(void) const { return "TestLogger"; }

    virtual void onRegisterCallbacks(Pipeline &) {}

private:
    std::string &_content;
};

Test(Log, CustomLogger)
{
    std::string content;
    LoggerPtr logger = std::make_shared<TestLogger>(content);

    Log::AddLogger(logger);
    Log() << "The key number is " << 42;
    cr_assert_eq(content, "The key number is 42\n");
}