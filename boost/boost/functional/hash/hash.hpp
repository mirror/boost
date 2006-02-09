
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_HASH_HASH_HPP)
#define BOOST_FUNCTIONAL_HASH_HASH_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/functional/hash_fwd.hpp>
#include <functional>
#include <boost/functional/detail/hash_float.hpp>
#include <boost/functional/detail/container_fwd.hpp>

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
#include <boost/type_traits/is_array.hpp>
#endif

namespace boost
{
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    // Borland complains about an ambiguous function overload
    // when compiling boost::hash<bool>.
    std::size_t hash_value(bool);
#endif
    
    std::size_t hash_value(int);
    std::size_t hash_value(unsigned int);
    std::size_t hash_value(long);
    std::size_t hash_value(unsigned long);

    template <class T> std::size_t hash_value(T* const&);

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    template< class T, unsigned N >
    std::size_t hash_value(const T (&array)[N]);

    template< class T, unsigned N >
    std::size_t hash_value(T (&array)[N]);
#endif

    std::size_t hash_value(float v);
    std::size_t hash_value(double v);
    std::size_t hash_value(long double v);

#if BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    template <class Ch, class A>
    std::size_t hash_value(std::basic_string<Ch, std::string_char_traits<Ch>, A> const&);
#else
    template <class Ch, class A>
    std::size_t hash_value(std::basic_string<Ch, std::char_traits<Ch>, A> const&);
#endif

    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const&);
    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const&);
    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v);
    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v);
    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v);
    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v);

    // Implementation

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    inline std::size_t hash_value(bool v)
    {
        return static_cast<std::size_t>(v);
    }
#endif

    inline std::size_t hash_value(int v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(unsigned int v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(long v)
    {
        return static_cast<std::size_t>(v);
    }

    inline std::size_t hash_value(unsigned long v)
    {
        return static_cast<std::size_t>(v);
    }

    // Implementation by Alberto Barbati and Dave Harris.
    template <class T> std::size_t hash_value(T* const& v)
    {
        std::size_t x = static_cast<std::size_t>(
           reinterpret_cast<std::ptrdiff_t>(v));
        return x + (x >> 3);
    }

#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    namespace hash_detail
    {
        template <bool IsArray>
        struct call_hash_impl
        {
            template <class T>
            struct inner
            {
                static std::size_t call(T const& v)
                {
                    using namespace boost;
                    return hash_value(v);
                }
            };
        };

        template <>
        struct call_hash_impl<true>
        {
            template <class Array>
            struct inner
            {
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
                static std::size_t call(Array& v)
#else
                static std::size_t call(Array const& v)
#endif
                {
                    const int size = sizeof(v) / sizeof(*v);
                    return boost::hash_range(v, v + size);
                }
            };
        };

        template <class T>
        struct call_hash
            : public call_hash_impl<boost::is_array<T>::value>
                ::BOOST_NESTED_TEMPLATE inner<T>
        {
        };
    }
#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    template <class T>
    inline void hash_combine(std::size_t& seed, T& v)
#else
    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
#endif
    {
        boost::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template <class It>
    inline std::size_t hash_range(It first, It last)
    {
        std::size_t seed = 0;

        for(; first != last; ++first)
        {
            hash_combine(seed, *first);
        }

        return seed;
    }

    template <class It>
    inline void hash_range(std::size_t& seed, It first, It last)
    {
        for(; first != last; ++first)
        {
            hash_combine(seed, *first);
        }
    }

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    template <class T>
    inline std::size_t hash_range(T* first, T* last)
    {
        std::size_t seed = 0;

        for(; first != last; ++first)
        {
            boost::hash<T> hasher;
            seed ^= hasher(*first) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        return seed;
    }

    template <class T>
    inline void hash_range(std::size_t& seed, T* first, T* last)
    {
        for(; first != last; ++first)
        {
            boost::hash<T> hasher;
            seed ^= hasher(*first) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
    }
#endif

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
    template< class T, unsigned N >
    inline std::size_t hash_value(const T (&array)[N])
    {
        return hash_range(array, array + N);
    }

    template< class T, unsigned N >
    inline std::size_t hash_value(T (&array)[N])
    {
        return hash_range(array, array + N);
    }
#endif

#if BOOST_WORKAROUND(__GNUC__, < 3) && !defined(__SGI_STL_PORT) && !defined(_STLPORT_VERSION)
    template <class Ch, class A>
    inline std::size_t hash_value(std::basic_string<Ch, std::string_char_traits<Ch>, A> const& v)
#else
    template <class Ch, class A>
    inline std::size_t hash_value(std::basic_string<Ch, std::char_traits<Ch>, A> const& v)
#endif
    {
        return hash_range(v.begin(), v.end());
    }

    inline std::size_t hash_value(float v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    inline std::size_t hash_value(double v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    inline std::size_t hash_value(long double v)
    {
        return boost::hash_detail::float_hash_value(v);
    }

    template <class A, class B>
    std::size_t hash_value(std::pair<A, B> const& v)
    {
        std::size_t seed = 0;
        hash_combine(seed, v.first);
        hash_combine(seed, v.second);
        return seed;
    }

    template <class T, class A>
    std::size_t hash_value(std::vector<T, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::list<T, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class T, class A>
    std::size_t hash_value(std::deque<T, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::set<K, C, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class K, class C, class A>
    std::size_t hash_value(std::multiset<K, C, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::map<K, T, C, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    template <class K, class T, class C, class A>
    std::size_t hash_value(std::multimap<K, T, C, A> const& v)
    {
        return hash_range(v.begin(), v.end());
    }

    // boost::hash

    template <class T> struct hash
        : std::unary_function<T, std::size_t>
    {
#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)
        std::size_t operator()(T const& val) const
        {
            return hash_value(val);
        }
#else
        std::size_t operator()(T const& val) const
        {
            return hash_detail::call_hash<T>::call(val);
        }

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
        std::size_t operator()(T& val) const
        {
            return hash_detail::call_hash<T>::call(val);
        }
#endif
#endif
    };
}

#endif

