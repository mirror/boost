///////////////////////////////////////////////////////////////////////////////
// utility.hpp header file
//
// Copyright 2005 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_FOREACH_TEST_UTILITY_HPP
#define BOOST_FOREACH_TEST_UTILITY_HPP

#include <vector>
#include <boost/config.hpp>
#include <boost/range/end.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include "../../../boost/foreach.hpp"

///////////////////////////////////////////////////////////////////////////////
// to_vector_for
//
template<typename Range>
inline std::vector<int> to_vector_for( Range & rng )
{
    std::vector<int> vect;
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Range>::type iterator;
    for(iterator begin = boost::begin(rng), end = boost::end(rng);
        begin != end; ++begin)
    {
        vect.push_back(*begin);
    }
    return vect;
}

///////////////////////////////////////////////////////////////////////////////
// to_vector_foreach_byval
//
template<typename Range>
inline std::vector<int> to_vector_foreach_byval( Range & rng )
{
    std::vector<int> vect;
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Range>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME boost::iterator_value<iterator>::type value;
    BOOST_FOREACH( value i, rng )
    {
        vect.push_back(i);
    }
    return vect;
}

///////////////////////////////////////////////////////////////////////////////
// to_vector_foreach_byref
//
template<typename Range>
inline std::vector<int> to_vector_foreach_byref( Range & rng )
{
    std::vector<int> vect;
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Range>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME boost::iterator_reference<iterator>::type reference;
    BOOST_FOREACH( reference i, rng )
    {
        vect.push_back(i);
    }
    return vect;
}

///////////////////////////////////////////////////////////////////////////////
// mutate_foreach_byref
//
template<typename Range>
inline void mutate_foreach_byref( Range & rng )
{
    typedef BOOST_DEDUCED_TYPENAME boost::range_result_iterator<Range>::type iterator;
    typedef BOOST_DEDUCED_TYPENAME boost::iterator_reference<iterator>::type reference;
    BOOST_FOREACH( reference i, rng )
    {
        ++i;
    }
}

#endif
