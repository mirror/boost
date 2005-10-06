///////////////////////////////////////////////////////////////////////////////
// algorithm.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_UTILITY_ALGORITHM_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_UTILITY_ALGORITHM_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <climits>
#include <algorithm>
#include <boost/iterator/iterator_traits.hpp>

namespace boost { namespace xpressive { namespace detail
{

///////////////////////////////////////////////////////////////////////////////
// any
//
template<typename InIterT, typename PredT>
inline bool any(InIterT begin, InIterT end, PredT pred)
{
    return end != std::find_if(begin, end, pred);
}

///////////////////////////////////////////////////////////////////////////////
// find_nth_if
//
template<typename FwdIterT, typename DiffT, typename PredT>
FwdIterT find_nth_if(FwdIterT begin, FwdIterT end, DiffT count, PredT pred)
{
    for(; begin != end; ++begin)
    {
        if(pred(*begin) && 0 == count--)
        {
            return begin;
        }
    }

    return end;
}

///////////////////////////////////////////////////////////////////////////////
// toi
//
template<typename InIterT, typename TraitsT>
int toi(InIterT &begin, InIterT end, TraitsT const &traits, int radix = 10, int max = INT_MAX)
{
    int i = 0, c = 0;
    for(; begin != end && -1 != (c = traits.value(*begin, radix)); ++begin)
    {
        if(max < ((i *= radix) += c))
            return i / radix;
    }
    return i;
}

///////////////////////////////////////////////////////////////////////////////
// advance_to
//
template<typename BidiIterT, typename DiffT>
inline bool advance_to_impl(BidiIterT & iter, DiffT diff, BidiIterT end, std::bidirectional_iterator_tag)
{
    for(; 0 < diff && iter != end; --diff)
        ++iter;
    for(; 0 > diff && iter != end; ++diff)
        --iter;
    return 0 == diff;
}

template<typename RandIterT, typename DiffT>
inline bool advance_to_impl(RandIterT & iter, DiffT diff, RandIterT end, std::random_access_iterator_tag)
{
    if(0 < diff)
    {
        if((end - iter) < diff)
            return false;
    }
    else if(0 > diff)
    {
        if((iter - end) < -diff)
            return false;
    }
    iter += diff;
    return true;
}

template<typename IterT, typename DiffT>
inline bool advance_to(IterT & iter, DiffT diff, IterT end)
{
    return detail::advance_to_impl(iter, diff, end, typename iterator_category<IterT>::type());
}

}}}

#endif
