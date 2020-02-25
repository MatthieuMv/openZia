/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: File system compiler abstraction
 */

#pragma once

#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "You compiler doesn't support std::filesystem nor std::experimental::filesystem"
#endif