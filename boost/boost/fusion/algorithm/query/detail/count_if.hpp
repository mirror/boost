/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COUNT_IF_09162005_0141)
#define FUSION_COUNT_IF_09162005_0141

#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, typename F>
    inline int
    count_if(First const&, Last const&, F const&, mpl::true_)
    {
        return 0;
    }

    template <typename First, typename Last, typename F>
    inline int
    count_if(First const& first, Last const& last, F& f, mpl::false_)
    {
        typename result_of::deref<First>::type x = *first;
        int n =  
            detail::count_if(
                fusion::next(first)
              , last
              , f
              , result_of::equal_to<typename result_of::next<First>::type, Last>());
        if (f(x))
            ++n;
        return n;
    }
}}}

#endif

