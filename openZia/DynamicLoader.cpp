/*
** EPITECH PROJECT, 2020
** openZia
** File description:
** DynamicLoader
*/

#include <stdexcept>

#include "DynamicLoader.hpp"

using namespace oZ;

DynamicLoader::~DynamicLoader()
{
    release();
}

void *DynamicLoader::getFunction(DynamicHandler handler, const std::string &name)
{
	void *function = nullptr;
#if defined(SYSTEM_LINUX)
    function = ::dlsym(handler, name.c_str());
#elif defined(SYSTEM_WINDOWS)
	function = ::GetProcAddress(handler, name.c_str());
#endif
    if (!function)
        throw std::runtime_error("DynamicLoader::getFunction: Couldn't find function '" + name + "' in handler '" + getHandlerPath(handler) + '\'');
    return function;
}

DynamicHandler DynamicLoader::load(const std::string &path)
{
    DynamicHandler handler = nullptr;

#if defined(SYSTEM_LINUX)
    handler = ::dlopen(path.c_str(), RTLD_LAZY);
#elif defined(SYSTEM_WINDOWS)
    handler = ::LoadLibrary(path.c_str());
#endif
    if (!handler)
        throw std::runtime_error("DynamicLoader::load: Couldn't load library '" + path + "'\n\t-> " + getLastError());
    _handlers[handler] = path;
    return handler;
}

void DynamicLoader::release(void)
{
    for (auto &[handler, name] : _handlers) {
#if defined(SYSTEM_LINUX)
        ::dlclose(handler);
#elif defined(SYSTEM_WINDOWS)
        ::FreeLibrary(handler);
#endif
    }
    _handlers.clear();
}

std::string DynamicLoader::getLastError(void) const noexcept
{
#if defined(SYSTEM_LINUX)
    return ::dlerror();
#elif defined(SYSTEM_WINDOWS)
    DWORD id = ::GetLastError();
    if (!id)
        return std::string();
    LPSTR buffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, id,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&buffer), 0, NULL
    );
    std::string message(buffer, size);
    LocalFree(buffer);
    return message;
#endif
}

std::string DynamicLoader::getHandlerPath(const DynamicHandler handler) const noexcept
{
    auto it = _handlers.find(handler);

    if (it == _handlers.end())
        return std::string();
    return it->second;
}