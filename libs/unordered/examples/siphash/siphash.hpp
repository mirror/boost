
// Copyright 2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is also released into the public domain.

#if !defined(BOOST_HASH_EXAMPLES_SIPHASH_HEADER)
#define BOOST_HASH_EXAMPLES_SIPHASH_HEADER

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>

#include <string>
#include <vector>
#include <list>

namespace hash
{
    // Random key used to make sure the hash function isn't predictable.

    struct sipkey
    {
        boost::uint64_t k0, k1;
    };

    // Generate a secure sipkey.
    // This only works when boost::random_device is available.
    sipkey generate_sipkey();

    // This is the class that does the actual hashing.

    struct siphash_state
    {
        boost::uint64_t v0, v1, v2, v3;
        union {
            boost::uint64_t m;
            unsigned char buffer[8];
        };
        unsigned char buffered;
        unsigned char b;

        explicit siphash_state(sipkey const&);
        void update(void const*, unsigned);
        boost::uint64_t finalize();

    private:
        void sip_round(unsigned);
    };

    // The genereric hash function.
    //
    // Don't sepecialize this. Unless you really want to.

    template <typename T>
    struct siphash
    {
        sipkey key;

        /* implicit */ siphash(sipkey const& k) : key(k) {}
        std::size_t operator()(T const&) const;
    };

    // Add support for a type by specializing this class.
    //
    // 'Enable' is used as a SFINAE hook.

    template <typename T, typename Enable = void>
    struct siphash_impl
    {
        static void update(siphash_state&, T const&);
    };

    // The implementation of the generic hash function.

    template <typename T>
    std::size_t siphash<T>::operator()(T const& x) const
    {
        siphash_state state(key);
        siphash_impl<T>::update(state, x);
        return static_cast<std::size_t>(state.finalize());
    }

    // A couple of basic traits for hashing binary data.

    struct enable_siphash_false { enum { value = false }; };
    struct enable_siphash_true { enum { value = true }; };

    template <typename T>
    struct enable_siphash_binary : enable_siphash_false {};

    template <typename T>
    struct enable_siphash_binary_array
    {
        enum { value = enable_siphash_binary<T>::value &&
            sizeof(T[2]) == sizeof(T) * 2 };
    };

    // Some general purpose hash implementations, siphash_impl<T>
    // can inherit from these.

    template <typename T>
    struct siphash_binary_impl
    {
        static void update(siphash_state& state, int x)
        {
            state.update(&x, sizeof(x));
        }
    };

    template <typename T>
    struct siphash_container_impl
    {
        static void update(siphash_state& state, T const& x)
        {
            siphash_impl<typename T::value_type> value_impl;

            for (typename T::const_iterator begin = x.begin(),
                end = x.end(); begin != end; ++begin)
            {
                value_impl.update(state, *begin);
            }
        }
    };

    template <typename T, bool Enable = enable_siphash_binary_array<T>::value>
    struct siphash_binary_container_impl;

    template <typename T>
    struct siphash_binary_container_impl<T, false> :
        siphash_container_impl<T> {};

    template <typename T>
    struct siphash_binary_container_impl<T, true>
    {
        static void update(siphash_state& state, T const& x)
        {
            state.update(&*x.cbegin(), sizeof(T) * x.size());
        }
    };

    // Specialize siphash_impl for various types.

    template <typename T>
    struct siphash_impl<T,
        typename boost::enable_if_c<enable_siphash_binary<T>::value>::type
    > : siphash_binary_impl<T> {};

    template <typename T, typename Alloc>
    struct siphash_impl<std::list<T, Alloc> > :
        siphash_container_impl<T> {};

    template <typename T, typename Alloc>
    struct siphash_impl<std::vector<T, Alloc> > :
        siphash_binary_container_impl<T> {};

    template <typename T, typename Alloc>
    struct siphash_impl<std::basic_string<T, std::char_traits<T>, Alloc> > :
        siphash_binary_container_impl<T> {};

    // Specialize the binary trait for builtin types.

    template <> struct enable_siphash_binary<bool> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<char> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<unsigned char> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<signed char> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<short> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<unsigned short> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<int> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<unsigned int> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<long> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<unsigned long> :
        enable_siphash_true {};

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    template <> struct enable_siphash_binary<wchar_t> :
        enable_siphash_true {};
#endif

#if !defined(BOOST_NO_LONG_LONG)
    template <> struct enable_siphash_binary<boost::long_long_type> :
        enable_siphash_true {};
    template <> struct enable_siphash_binary<boost::ulong_long_type> :
        enable_siphash_true {};
#endif

#if defined(BOOST_HAS_INT128)
    template <> struct enable_siphash_binary<boost::int128_type> :
        boost::hash_detail::enable_hash_value {};
    template <> struct enable_siphash_binary<boost::uint128_type> :
        boost::hash_detail::enable_hash_value {};
#endif
}

#endif
