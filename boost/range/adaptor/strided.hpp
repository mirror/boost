// Boost.Range library
//
//  Copyright Neil Groves 2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ADAPTOR_STRIDED_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_STRIDED_HPP_INCLUDED

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <iterator>

#include <iostream>

namespace boost
{
    namespace range_detail
    {

        template<class BaseIterator>
        class strided_iterator
            : public iterator_adaptor<
                strided_iterator<BaseIterator>
              , BaseIterator
            >
        {
            friend class iterator_core_access;

            typedef iterator_adaptor<strided_iterator<BaseIterator>, BaseIterator> super_t;

        public:
            typedef BOOST_DEDUCED_TYPENAME std::iterator_traits<BaseIterator>::difference_type difference_type;

            strided_iterator()
                : m_stride(), m_offset(), m_max_offset()
            {
            }

            explicit strided_iterator(BaseIterator base_it,
                                      difference_type stride,
                                      difference_type offset,
                                      difference_type max_offset)
                : super_t(base_it)
                , m_stride(stride)
                , m_offset(offset)
                , m_max_offset(max_offset)
            {
            }

            template<class OtherIterator>
            strided_iterator(const strided_iterator<OtherIterator>& other,
                             BOOST_DEDUCED_TYPENAME enable_if_convertible<OtherIterator, BaseIterator>::type* = 0)
                : super_t(other)
                , m_stride(other.m_stride)
                , m_offset(other.m_offset)
                , m_max_offset(other.m_max_offset)
            {
            }

            strided_iterator&
            operator=(const strided_iterator& other)
            {
                super_t::operator=(other);
                m_stride = other.m_stride;
                m_offset = other.m_offset;
                m_max_offset = other.m_max_offset;
                return *this;
            }

            void increment()
            {
                m_offset += m_stride;
                if (m_offset <= m_max_offset)
                    std::advance(this->base_reference(), m_stride);
            }

            void decrement()
            {
                m_offset -= m_stride;
                if (m_offset >= 0)
                    std::advance(this->base_reference(), -m_stride);
            }

            void advance(difference_type n)
            {
                n *= m_stride;
                m_offset += n;

                if (m_offset >= 0 && m_offset <= m_max_offset)
                    std::advance(this->base_reference(), n);
            }

            template<class OtherIterator>
            bool equal(const strided_iterator<OtherIterator>& other,
                       BOOST_DEDUCED_TYPENAME enable_if_convertible<OtherIterator, BaseIterator>::type* = 0) const
            {
                return m_offset == other.m_offset;
            }

            difference_type
            distance_to(const strided_iterator& other) const
            {
                return (other.m_offset - m_offset) / m_stride;
            }

        private:
            difference_type m_stride;
            difference_type m_offset;
            difference_type m_max_offset;
        };

        template<class BaseIterator, class Difference> inline
        strided_iterator<BaseIterator>
        make_strided_iterator(
            const BaseIterator& first,
            Difference          stride,
            typename std::iterator_traits<BaseIterator>::difference_type offset,
            typename std::iterator_traits<BaseIterator>::difference_type max_offset
            )
        {
            BOOST_ASSERT( stride >= 0 );
            BOOST_ASSERT( (stride == 0) || (offset % stride == 0) );
            BOOST_ASSERT( (stride == 0) || (max_offset % stride == 0) );
            BOOST_ASSERT( offset <= max_offset );
            return strided_iterator<BaseIterator>(first, stride, offset, max_offset);
        }

        template< class Rng >
        class strided_range
            : public iterator_range<range_detail::strided_iterator<BOOST_DEDUCED_TYPENAME range_iterator<Rng>::type> >
        {
            typedef range_detail::strided_iterator<BOOST_DEDUCED_TYPENAME range_iterator<Rng>::type> iter_type;
            typedef iterator_range<iter_type> super_t;
        public:
            template<class Difference>
            strided_range(Difference stride, Rng& rng)
                : super_t(make_super(stride, rng))
            {
                BOOST_ASSERT( stride >= 0 );
            }

        private:
            template<class Difference>
            static super_t make_super(const Difference stride, Rng& rng)
            {
                const Difference count = boost::size(rng);
                const Difference max_count = max_offset(count, stride);
                return super_t(make_strided_iterator(boost::begin(rng), stride, 0, max_count),
                               make_strided_iterator(boost::end(rng), stride, max_count, max_count));
            }

            template<class Difference, class Stride>
            static Difference max_offset(Difference sz, const Stride stride)
            {
                if (stride > 0)
                {
                    sz += stride - 1;
                    sz /= stride;
                    sz *= stride;
                }
                return sz;
            }
        };

        template<class Difference>
        class strided_holder : public holder<Difference>
        {
        public:
            explicit strided_holder(Difference value) : holder<Difference>(value) {}
        };

        template<class Rng, class Difference>
        inline strided_range<Rng>
        operator|(Rng& rng, const strided_holder<Difference>& stride)
        {
            return strided_range<Rng>(stride.val, rng);
        }

        template<class Rng, class Difference>
        inline strided_range<const Rng>
        operator|(const Rng& rng, const strided_holder<Difference>& stride)
        {
            return strided_range<const Rng>(stride.val, rng);
        }

    } // namespace range_detail

    using range_detail::strided_range;

    namespace adaptors
    {

        namespace
        {
            const range_detail::forwarder<range_detail::strided_holder>
                strided = range_detail::forwarder<range_detail::strided_holder>();
        }

        template<class Range, class Difference>
        inline strided_range<Range>
        stride(Range& rng, Difference step)
        {
            return strided_range<Range>(step, rng);
        }

        template<class Range, class Difference>
        inline strided_range<const Range>
        stride(const Range& rng, Difference step)
        {
            return strided_range<const Range>(step, rng);
        }

    } // namespace 'adaptors'
} // namespace 'boost'

#endif
