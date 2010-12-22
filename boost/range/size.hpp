// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SIZE_HPP
#define BOOST_RANGE_SIZE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/assert.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class SinglePassRange >
        inline BOOST_DEDUCED_TYPENAME range_difference<SinglePassRange>::type
        size_impl(const SinglePassRange& rng, boost::single_pass_traversal_tag)
        {
            typedef BOOST_DEDUCED_TYPENAME range_difference<SinglePassRange>::type diff_t;

            // A compilation error here will often indicate that an algorithm
            // is attempting to use boost::size(rng) for a range that is not a
            // model of the RandomAccessRange Concept and does not have a
            // member size() function.
            // The solution to this issue is to add a range_calculate_size()
            // function for the range type that will be found via ADL.
            return static_cast<diff_t>(rng.size());
        }

        template< class SinglePassRange >
        inline BOOST_DEDUCED_TYPENAME range_difference<SinglePassRange>::type
        size_impl(const SinglePassRange& rng, boost::random_access_traversal_tag)
        {
            BOOST_ASSERT( (boost::end(rng) - boost::begin(rng)) >= 0 &&
                          "reachability invariant broken!" );
            return boost::end(rng) - boost::begin(rng);
        }
    } // namespace range_detail

    template<class SinglePassRange>
    inline BOOST_DEDUCED_TYPENAME range_difference<SinglePassRange>::type
    range_calculate_size(const SinglePassRange& rng)
    {
        typedef BOOST_DEDUCED_TYPENAME range_iterator<const SinglePassRange>::type iter_t;
        typedef BOOST_DEDUCED_TYPENAME iterator_traversal<iter_t>::type traversal_tag;
        return range_detail::size_impl(rng, traversal_tag());
    }

    template<class SinglePassRange>
    inline BOOST_DEDUCED_TYPENAME range_difference<SinglePassRange>::type
    size(const SinglePassRange& rng)
    {
        return range_calculate_size(rng);
    }

} // namespace 'boost'

#endif
