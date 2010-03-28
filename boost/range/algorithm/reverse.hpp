//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_REVERSE_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_REVERSE_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/detail/range_return.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function reverse
    ///
    /// range-based version of the reverse std algorithm
    ///
    /// \pre BidirectionalRange is a model of the BidirectionalRangeConcept
    template<class BidirectionalRange>
    inline BidirectionalRange& reverse(BidirectionalRange& rng)
    {
        boost::function_requires< BidirectionalRangeConcept<BidirectionalRange> >();
		std::reverse(boost::begin(rng), boost::end(rng));
        return rng;
    }

    /// \overload
    template<class BidirectionalRange>
    inline const BidirectionalRange& reverse(const BidirectionalRange& rng)
    {
        boost::function_requires< BidirectionalRangeConcept<BidirectionalRange> >();
		std::reverse(boost::begin(rng), boost::end(rng));
        return rng;
    }
}

#endif // include guard
