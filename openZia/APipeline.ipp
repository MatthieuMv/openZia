/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Pipeline Abstraction
*/

template<typename Type>
std::shared_ptr<Type> oZ::APipeline::findModule(void) const
{
    for (auto &module : _modules)
        if (auto ptr = std::dynamic_pointer_cast<Type>(module); ptr)
            return ptr;
    return std::shared_ptr<Type>();
}