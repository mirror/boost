//-----------------------------------------------------------------------------
// boost mpl/aux_/erase_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED

#include "boost/mpl/clear.hpp"
#include "boost/mpl/push_front.hpp"
#include "boost/mpl/copy_backward.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the |erase_traits| or the primary |erase| template

template< typename Tag >
struct erase_traits
{
    template<
          typename Sequence
        , typename First
        , typename Last
        >
    struct algorithm
    {
     private:
        // 1st half: [begin, first)
        typedef iterator_range<
              typename begin<Sequence>::type
            , First
            > first_half_;

        // 2nd half: [last, end) ... that is, [last + 1, end)
        typedef iterator_range<
              Last
            , typename end<Sequence>::type
            > second_half_;

        typedef typename copy_backward<
              second_half_
            , typename clear<Sequence>::type
            , push_front<_,_>
            >::type half_sequence_;

     public:
        typedef typename copy_backward<
              first_half_
            , half_sequence_
            , push_front<_,_>
            >::type type;
    };

};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_ERASE_IMPL_HPP_INCLUDED
