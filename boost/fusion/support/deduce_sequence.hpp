/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/sequence/conversion/as_vector.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/mpl/transform.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <class Sequence> struct deduce_sequence;

    namespace detail
    {
        struct deducer
        {
            template <typename T>
            struct apply
                : fusion::traits::deduce<T>
            { };
        };
    }

    // We cannot use fusion::transform_view here as result_of loses cv qualifiers
    // on built in types
    template <class Sequence>
    struct deduce_sequence
        : result_of::as_vector<
            typename mpl::transform<Sequence, detail::deducer>::type>
    { };

}}}

#endif

