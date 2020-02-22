/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Context Abstraction
*/

template<typename Type>
void oZ::Context::setMetadata(const std::string &key, Type value)
{
    _metadata.insert(std::make_pair(key, value));
}

template<typename Type>
Type &oZ::Context::getMetadata(const std::string &key)
{
    return std::any_cast<Type>(_metadata.find(key)->second);
}

template<typename Type>
const Type &oZ::Context::getMetadata(const std::string &key) const
{
    return std::any_cast<Type>(_metadata.find(key)->second);
}
