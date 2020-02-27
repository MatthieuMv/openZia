/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** Module Interface
*/

// Pipeline forward declaration
#include "IModule.hpp"

// Pipeline declaration
#include "Pipeline.hpp"

using namespace oZ;

void IModule::onRetrieveDependencies(Pipeline &)
{
}

void IModule::onLoadConfigurationFile(const std::string &)
{
}

void IModule::onConnection(Context &)
{
}

void IModule::onDisconnection(Context &)
{
}

MessageState IModule::onMessageAvailable(Context &)
{
    return MessageState::Readable;
}
