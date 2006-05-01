// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_LIBS_CONCEPT_CHECK_FAKE_SORT_DWA2006430_HPP
# define BOOST_LIBS_CONCEPT_CHECK_FAKE_SORT_DWA2006430_HPP

# include <boost/detail/iterator.hpp>
# include <boost/concept_check/where.hpp>
# include <boost/concept_check.hpp>

template<typename RanIter>
BOOST_CONCEPT_WHERE(
    ((boost::Mutable_RandomAccessIteratorConcept<RanIter>))
    ((boost::LessThanComparableConcept<typename boost::detail::iterator_traits<RanIter>::value_type>))
    
  , (void))
fake_sort(RanIter,RanIter)
{
 
}

#endif // BOOST_LIBS_CONCEPT_CHECK_FAKE_SORT_DWA2006430_HPP
