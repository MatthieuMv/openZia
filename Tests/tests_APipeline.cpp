/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline Abstraction 
*/

#include <criterion/criterion.h>

#include <openZia/APipeline.hpp>

using namespace oZ;

template<typename Callback>
class Pipeline : public APipeline
{
public:
    Pipeline(Callback &&cb) : _cb(std::move(cb)) {}
    virtual ~Pipeline(void) = default;

    virtual void onLoadModules(const std::string & = std::string()) { _cb(); }

private:
    Callback _cb;
};

Test(APipeline, Basics)
{
    Pipeline pipeline([]{
        
    });

    cr_assert(pipeline.getModules().empty());
}