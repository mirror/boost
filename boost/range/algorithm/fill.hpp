//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_FILL_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_FILL_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <algorithm>

namespace boost
{
    /// \brief template function fill
    ///
    /// range-based version of the fill std algorithm
    ///
    /// \pre ForwardRange is a model of the ForwardRangeConcept
    template< class ForwardRange, class Value >
    inline ForwardRange& fill(ForwardRange& rng, const Value& val)
    {
        boost::function_requires< ForwardRangeConcept<ForwardRange> >();
        std::fill(boost::begin(rng), boost::end(rng), val);
        return rng;
    }
}

#endif // include guard
