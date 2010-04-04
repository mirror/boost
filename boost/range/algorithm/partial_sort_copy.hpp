//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_PARTIAL_SORT_COPY_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_PARTIAL_SORT_COPY_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/value_type.hpp>
#include <algorithm>

namespace boost
{
    namespace range
    {

/// \brief template function partial_sort_copy
///
/// range-based version of the partial_sort_copy std algorithm
///
/// \pre SinglePassRange is a model of the SinglePassRangeConcept
/// \pre RandomAccessRange is a model of the Mutable_RandomAccessRangeConcept
/// \pre BinaryPredicate is a model of the BinaryPredicateConcept
template<typename SinglePassRange, typename RandomAccessRange>
inline typename range_iterator<RandomAccessRange>::type
partial_sort_copy(const SinglePassRange& rng1, RandomAccessRange& rng2)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange>));
    BOOST_RANGE_CONCEPT_ASSERT((WriteableRandomAccessRangeConcept<RandomAccessRange>));
    BOOST_RANGE_CONCEPT_ASSERT((range_detail::SameTypeConcept<typename range_value<SinglePassRange>::type, typename range_value<RandomAccessRange>::type>));
    BOOST_RANGE_CONCEPT_ASSERT((LessThanComparableConcept<typename range_value<SinglePassRange>::type>));

    return std::partial_sort_copy(boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2));
}

/// \overload
template<typename SinglePassRange, typename RandomAccessRange,
         typename BinaryPredicate>
inline typename range_iterator<RandomAccessRange>::type
partial_sort_copy(const SinglePassRange& rng1, RandomAccessRange& rng2,
    BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange>));
    BOOST_RANGE_CONCEPT_ASSERT((WriteableRandomAccessRangeConcept<RandomAccessRange>));
    BOOST_RANGE_CONCEPT_ASSERT((range_detail::SameTypeConcept<typename range_value<SinglePassRange>::type, typename range_value<RandomAccessRange>::type>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate, typename range_value<RandomAccessRange>::type, typename range_value<RandomAccessRange>::type>));

    return std::partial_sort_copy(boost::begin(rng1), boost::end(rng1),
        boost::begin(rng2), boost::end(rng2), pred);
}

    } // namespace range
    using range::partial_sort_copy;
} // namespace boost

#endif // include guard
