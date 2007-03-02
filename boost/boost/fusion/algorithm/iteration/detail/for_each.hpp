/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FOR_EACH_05052005_1028)
#define FUSION_FOR_EACH_05052005_1028

#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename First, typename Last, typename F>
    inline void
    for_each(First const&, Last const&, F const&, mpl::true_)
    {
    }

    template <typename First, typename Last, typename F>
    inline void
    for_each(First const& first, Last const& last, F const& f, mpl::false_)
    {
        f(*first);
        detail::for_each(fusion::next(first), last, f
            , result_of::equal_to<typename result_of::next<First>::type, Last>());
    }
}}}

#endif

