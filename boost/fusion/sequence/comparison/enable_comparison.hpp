/*=============================================================================
    Copyright (c) 2001-2006 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Sequence, typename Enable = void>
    struct is_native_fusion_sequence
      : is_convertible<Sequence, detail::from_sequence_convertible_type>
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::or_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            mpl::or_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif
