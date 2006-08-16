/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2006 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_0431)
#define FUSION_EQUAL_TO_05052005_0431

#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/sequence/comparison/detail/enable_comparison.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace sequence_operators
    {
        template <typename Seq1, typename Seq2>
        inline typename 
        enable_if<
            detail::enable_equality<Seq1, Seq2>
            , bool
            >::type
        operator==(Seq1 const& a, Seq2 const& b)
        {
            return result_of::size<Seq1>::value == result_of::size<Seq2>::value
                && detail::sequence_equal_to<
                Seq1 const, Seq2 const
                , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
                call(fusion::begin(a), fusion::begin(b));
        }
    }
    using sequence_operators::operator==;
}}

#endif
