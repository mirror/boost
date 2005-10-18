///////////////////////////////////////////////////////////////////////////////
// traits_utils.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_UTILITY_TRAITS_UTILS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_UTILITY_TRAITS_UTILS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
# pragma warning(push)
# pragma warning(disable : 4100) // unreferenced formal parameter
#endif

#include <string>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // char_cast
    //
    template<typename ToCharT, typename FromCharT, typename TraitsT>
    inline ToCharT
    char_cast(FromCharT from, TraitsT const &, typename enable_if<is_same<ToCharT, FromCharT> >::type * = 0)
    {
        return from;
    }

    template<typename ToCharT, typename FromCharT, typename TraitsT>
    inline ToCharT
    char_cast(FromCharT from, TraitsT const &traits, typename disable_if<is_same<ToCharT, FromCharT> >::type * = 0)
    {
        BOOST_MPL_ASSERT((is_same<FromCharT, char>));
        return traits.widen(from);
    }

    ///////////////////////////////////////////////////////////////////////////////
    // string_cast
    //
    template<typename ToCharT, typename FromCharT, typename TraitsT>
    inline std::basic_string<ToCharT> const &
    string_cast(std::basic_string<FromCharT> const &from, TraitsT const &, typename enable_if<is_same<ToCharT, FromCharT> >::type * = 0)
    {
        return from;
    }

    template<typename ToCharT, typename FromCharT, typename TraitsT>
    inline std::basic_string<ToCharT> const
    string_cast(std::basic_string<FromCharT> const &from, TraitsT const &traits, typename disable_if<is_same<ToCharT, FromCharT> >::type * = 0)
    {
        BOOST_MPL_ASSERT((is_same<FromCharT, char>));
        std::basic_string<ToCharT> to;
        to.reserve(from.size());
        for(typename std::basic_string<FromCharT>::size_type i = 0; i < from.size(); ++i)
        {
            to.push_back(traits.widen(from[i]));
        }
        return to;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // translate
    //
    template<typename CharT, typename TraitsT>
    inline CharT translate(CharT ch, TraitsT const &traits, mpl::false_) // case-sensitive
    {
        return traits.translate(ch);
    }

    template<typename CharT, typename TraitsT>
    inline CharT translate(CharT ch, TraitsT const &traits, mpl::true_) // case-insensitive
    {
        return traits.translate_nocase(ch);
    }

}}} // namespace boost::xpressive::detail

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma warning(pop)
#endif

#endif
