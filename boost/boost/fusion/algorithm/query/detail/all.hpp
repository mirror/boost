/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ALL_05052005_1237)
#define FUSION_ALL_05052005_1237

#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, typename F>
    inline bool
    all(First const&, Last const&, F const&, mpl::true_)
    {
        return true;
    }

    template <typename First, typename Last, typename F>
    inline bool
    all(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        return f(x) && 
            detail::all(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }
}}}

#endif

