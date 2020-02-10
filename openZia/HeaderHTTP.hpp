/*
** EPITECH PROJECT, 2020
** CPP_zia_2019
** File description:
** HeaderHTTP
*/

#pragma once

#include <map>

#include "BaseHTTP.hpp"

// Verbose declaration needed for doxygen support
namespace oZ
{
    namespace HTTP
    {
        class Header;

        struct InsensitiveCompare
        {
            [[nodiscard]] bool operator()(const std::string &s1, const std::string &s2) const noexcept {
                return std::lexicographical_compare(
                    s1.begin(), s1.end(), s2.begin(), s2.end(),
                    [](char c1, char c2) { return ::tolower(c1) < ::tolower(c2); });
            }
        };

        using StringMultimap = std::multimap<std::string, std::string, InsensitiveCompare>;
    }
}

/**
 * @brief The HTTP Header is a simple map of string used to store header values
 */
class oZ::HTTP::Header
{
public:
    using Iterator = StringMultimap::iterator;
    using ConstIterator = StringMultimap::const_iterator;
    using IteratorRange = std::pair<Iterator, Iterator>;
    using ConstIteratorRange = std::pair<ConstIterator, ConstIterator>;

    /**
     * @brief Check existence of a value in the header
     */
    template<typename Literal>
    [[nodiscard]] bool exists(const Literal &key) const noexcept { return _mmap.find(key) != _mmap.end(); }

    /**
     * @brief Get a value in the header matching a key and an index, and throw if not found
     */
    template<typename Literal>
    [[nodiscard]] std::string &get(const Literal &key, const std::uint32_t index = 0);

    /**
     * @brief Get a value in the header matching a key and an index, and throw if not found
     */
    template<typename Literal>
    [[nodiscard]] const std::string &get(const Literal &key, const std::uint32_t index = 0) const;

    /**
     * @brief Get a value in the header
     */
    template<typename Literal, typename Literal2>
    void set(const Literal &key, Literal2 &&value) { _mmap.emplace(key, std::forward<Literal2>(value)); }

    /**
     * @brief Count occurences of matching key
     */
    template<typename Literal>
    [[nodiscard]] std::uint32_t count(const Literal &key) const noexcept { return _mmap.count(key); }

    /**
     * @brief Get the iterator of matching key
     */
    template<typename Literal>
    [[nodiscard]] Iterator getIterator(const Literal &key) { return _mmap.find(key); }

    /**
     * @brief Get the iterator of matching key
     */
    template<typename Literal>
    [[nodiscard]] ConstIterator getIterator(const Literal &key) const { return _mmap.find(key); }

    /**
     * @brief Get the iterator range of matching key
     */
    template<typename Literal>
    [[nodiscard]] IteratorRange getIteratorRange(const Literal &key) { return _mmap.equal_range(key); }

    /**
     * @brief Get the iterator range of matching key
     */
    template<typename Literal>
    [[nodiscard]] ConstIteratorRange getIteratorRange(const Literal &key) const { return _mmap.equal_range(key); }

    /**
     * @brief Get the String Multimap's reference
     */
    [[nodiscard]] StringMultimap &getStringMultimap(void) noexcept { return _mmap; }

    /**
     * @brief Get the String Multimap's constant reference
     */
    [[nodiscard]] const StringMultimap &getStringMultimap(void) const noexcept { return _mmap; }

private:
    StringMultimap _mmap {};
};

#include "HeaderHTTP.ipp"