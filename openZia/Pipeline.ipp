/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline Abstraction
*/

template<typename ModuleType>
void oZ::Pipeline::registerCallback(State state, Priority priority, ModuleType *target, bool(ModuleType::*callback)(Context &))
{
    registerCallback(state, priority, [target, callback](Context &context) {
        return (target->*callback)(context);
    });
}

template<typename Type, typename ...Args>
void oZ::Pipeline::addModule(Args &&...args)
{
    addModule(std::make_shared<Type>(std::forward<Args>(args)...));
}

template<typename Type>
std::shared_ptr<Type> oZ::Pipeline::findModule(void) const
{
    for (auto &module : _modules)
        if (auto ptr = std::dynamic_pointer_cast<Type>(module); ptr)
            return ptr;
    return std::shared_ptr<Type>();
}