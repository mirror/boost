// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ADAPTOR_TYPE_ERASED_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_TYPE_ERASED_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/range_reference.hpp>
#include <boost/range/range_value.hpp>

namespace boost
{
    namespace range_detail
    {
        template<
            class Value,
            class CategoryOrTraversal,
            class Reference,
            class Difference
            >
        class any_range
            : public iterator_range<
                        IteratorTypeErasure::any_iterator<
                            Value, CategoryOrTraversal, Reference, Difference> >
        {
            typedef typename IteratorTypeErasure::any_iterator<
                Value, CategoryOrTraversal, Reference, Difference> iterator_t;

            typedef iterator_range<iterator_t> base_t;
        public:
            template<class Range>
            explicit any_range(Range& r) : base_t(r) {}

            template<class Range>
            explicit any_range(const Range& r) : base_t(r) {}
        };

            template<class Range>
            class any_range_generator
            {
            public:
                typedef any_range<
                            BOOST_DEDUCED_TYPENAME range_value<Range>::type,
                            BOOST_DEDUCED_TYPENAME iterator_traversal<
                                BOOST_DEDUCED_TYPENAME range_iterator<Range>::type
                            >::type,
                            BOOST_DEDUCED_TYPENAME range_reference<Range>::type,
                            BOOST_DEDUCED_TYPENAME range_difference<Range>::type
                        > type;
            };

            class type_erased_tag {};


    } // namespace range_detail

    using range_detail::any_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::type_erased_tag type_erased = range_detail::type_erased_tag();
        }

        template<class SinglePassRange>
        typename range_detail::any_range_generator<SinglePassRange>::type
        operator|(SinglePassRange& rng, range_detail::type_erased_tag)
        {
            typedef typename range_detail::any_range_generator<SinglePassRange>::type range_t;
            return range_t(rng);
        }

        template<class SinglePassRange>
        typename range_detail::any_range_generator<const SinglePassRange>::type
        operator|(const SinglePassRange& rng, range_detail::type_erased_tag)
        {
            typedef typename range_detail::any_range_generator<const SinglePassRange>::type range_t;
            return range_t(rng);
        }
    }
} // namespace boost

#endif // include guard
