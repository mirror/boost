// Boost.Range library
//
//  Copyright Thorsten Ottosen & Pavol Droba 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ITERATOR_RANGE_HPP
#define BOOST_RANGE_ITERATOR_RANGE_HPP

#include <boost/range/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <iterator>
#include <algorithm>
#include <ostream>
#include <cstddef>


/*! \file
    Defines the \c iterator_class and related functions. 
    \c iterator_range is a simple wrapper of iterator pair idiom. It provides
    a rich subset of Container interface.
*/

namespace boost {

//  iterator range template class -----------------------------------------//

        //! iterator_range class
        /*!
            An \c iterator_range delimits a range in a sequence by beginning and ending iterators. 
            An iterator_range can be passed to an algorithm which requires a sequence as an input. 
            For example, the \c toupper() function may be used most frequently on strings, 
            but can also be used on iterator_ranges: 
            
            \code
                boost::tolower( find( s, "UPPERCASE STRING" ) );
            \endcode

            Many algorithms working with sequences take a pair of iterators, 
            delimiting a working range, as an arguments. The \c iterator_range class is an 
            encapsulation of a range identified by a pair of iterators. 
            It provides a collection interface, 
            so it is possible to pass an instance to an algorithm requiring a collection as an input. 
        */
        template<typename IteratorT> 
        class iterator_range
        {
        public:
            //! this type
            typedef iterator_range<IteratorT> type;
            //! Encapsulated value type
            typedef BOOST_DEDUCED_TYPENAME boost::
                iterator_value<IteratorT>::type value_type;
            //! Difference type
            typedef BOOST_DEDUCED_TYPENAME boost::
                iterator_difference<IteratorT>::type difference_type;
            //! Size type
            typedef std::size_t size_type; // note: must be unsigned
            
            //! const_iterator type
            /*! 
                There is no distinction between const_iterator and iterator.
                These typedefs are provides to fulfill container interface
            */ 
            typedef IteratorT const_iterator;
            //! iterator type
            typedef IteratorT iterator;

            //! Default constructor
            iterator_range() {}
            
            //! Constructor from a pair of iterators
            iterator_range( iterator Begin, iterator End ) : 
                m_Begin(Begin), m_End(End) {}

            //! Constructor from a Range
            template< class Range >
            iterator_range( const Range& r ) : 
                m_Begin( boost::begin( r ) ), m_End( boost::end( r ) ) {}

            //! Constructor from a Range
            template< class Range >
            iterator_range( Range& r ) : 
            m_Begin( boost::begin( r ) ), m_End( boost::end( r ) ) {}

            //! Copy constructor -- default OK

            //! Templated copy constructor
            /*!
                This constructor is provided to allow conversion between
                const and mutable iterator instances of this class template
            */
            template< typename OtherItT >
            iterator_range( const iterator_range<OtherItT>& Other ) :
                m_Begin(Other.begin()), m_End(Other.end()) {}

            //! Assignment operator -- defefault OK

            //! Assignment operator ( templated version )
            template< typename OtherItT >
            iterator_range& operator=( const iterator_range<OtherItT>& Other )
            {
                m_Begin=Other.begin(); m_End=Other.end();
                return *this;
            }
            
            //! Comparison operator ( equal )
            /*! 
                Compare operands for equality
            */
            template< typename OtherItT > 
            bool operator==( const iterator_range<OtherItT>& Other ) const
            {
                return ! (*this != Other);
            }

            //! Comparison operator ( not-equal )
            /*! 
                Compare operands for non-equality
            */
            template< typename OtherItT > 
            bool operator!=( const iterator_range<OtherItT>& Other ) const
            {
                return m_Begin!=Other.begin() || m_End!=Other.end();
            }

            //! begin access
            /*! 
                Retrieve the begin iterator
            */
            IteratorT begin() const 
            { 
                return m_Begin; 
            }

            //! end access
            /*!
                Retrieve the end iterator
            */
            IteratorT end() const 
            { 
                return m_End; 
            } 

            //! Size of the range
            /*!
                Retrieve the size of the range
            */
            size_type size() const
            { 
                return std::distance( m_Begin, m_End );
            }
            
            bool empty() const
            {
                return m_Begin == m_End;
            }

            //! Swap
            /*!
                Swap two ranges
            */
            void swap( iterator_range& Other )
            {
                std::swap( m_Begin, Other.m_Begin );
                std::swap( m_End, Other.m_End );
            }
            
            //! Safe bool conversion
            /*!
                Check whenever the range is empty.
                Allows to use construction like this:
                \code
                    iterator_range r;
                    if (!r)
                    {
                    ...
                    }
                \endcode
            */
            typedef iterator (iterator_range::*unspecified_bool_type) () const;
            operator unspecified_bool_type() const
            {
                return empty() ? 0: &iterator_range::end;
            }
            
            /*
            inline operator t_type() const
            {
                return make_tuple( m_Begin, m_End );
            }*/

        private:
            // begin and end iterators
            IteratorT m_Begin;
            IteratorT m_End;
        };

//  iterator range free-standing operators ---------------------------//

        //! iterator_range output operator
        /*!
            Output the range to an ostream. Elements are outputed
            in a sequence without separators.
        */
        template< typename IteratorT, typename Elem, typename Traits >
        std::basic_ostream<Elem,Traits>& operator<<( 
            std::basic_ostream<Elem, Traits>& Os,
            const iterator_range<IteratorT>& r )
        {
            std::copy( begin(r), end(r), std::ostream_iterator<Elem>(Os));

            return Os;
        }


//  iterator range utilities -----------------------------------------//

        //! iterator_range construct helper 
        /*!
            Construct an \c iterator_range from a pair of iterators

            \param Begin A begin iterator
            \param End An end iterator
            \return iterator_range object
        */
        template< typename IteratorT >
        inline iterator_range< IteratorT > 
        make_iterator_range( IteratorT Begin, IteratorT End ) 
        {   
            return iterator_range<IteratorT>( Begin, End );
        }
      
        //! iterator_range construct helper
        /*!
            Construct an \c iterator_range from a \c Range containing the begin
            and end iterators.
        */
        template< typename Range >
        inline iterator_range< BOOST_DEDUCED_TYPENAME iterator_of<Range>::type >
        make_iterator_range( Range& r ) 
        {   
            return iterator_range< BOOST_DEDUCED_TYPENAME iterator_of<Range>::type >
                ( r );
        }

        template< typename Range >
        inline iterator_range< BOOST_DEDUCED_TYPENAME const_iterator_of<Range>::type >
        make_iterator_range( const Range& r ) 
        {   
            return iterator_range< BOOST_DEDUCED_TYPENAME const_iterator_of<Range>::type >
                ( r );
        }

        //! copy a range into a sequence
        /*!
            Construct a new sequence of the specified type from the elements
            in the given range

            \param Range An input range
            \return New sequence
        */
        template< typename SeqT, typename Range >
        inline SeqT copy_range( const Range& r )
        {
            return SeqT( begin( r ), end( r ) );
        }

        //! transform a range into a sequence
        /*!
            Create a new sequence from the elements in the range, transformed
            by a function

            \param Range An input range
            \param Func Transformation function
            \return New sequence
        */
        template< typename SeqT, typename Range, typename FuncT >
        inline SeqT transform_range( const Range& r, FuncT Func )
        {
            SeqT Seq;
            std::transform( begin( r ), end( r ), std::back_inserter(Seq), Func );
            return Seq;
        }

} // namespace 'boost'


#endif
