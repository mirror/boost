//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_COPY_N_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_COPY_N_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/distance.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function copy
    ///
    /// range-based version of the copy std algorithm
    ///
    /// \pre SinglePassRange is a model of the SinglePassRangeConcept
    /// \pre OutputIterator is a model of the OutputIteratorConcept
    /// \pre 0 <= n < distance(rng)
    template< class SinglePassRange, class Size, class OutputIterator >
    inline OutputIterator copy_n(const SinglePassRange& rng, Size n, OutputIterator out)
    {
        boost::function_requires< SinglePassRangeConcept<SinglePassRange> >();
        BOOST_ASSERT( n < static_cast<Size>(boost::distance(rng)) );
        BOOST_ASSERT( n >= static_cast<Size>(0) );

        BOOST_DEDUCED_TYPENAME range_const_iterator<SinglePassRange>::type source = boost::begin(rng);

        for (Size i = 0; i < n; ++i, ++out, ++source)
            *out = *source;

        return out;
    }
}

#endif // include guard
