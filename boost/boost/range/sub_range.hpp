// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_SUB_RANGE_HPP
#define BOOST_RANGE_SUB_RANGE_HPP

#include <boost/range/config.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/range/size_type.hpp>
#include <boost/range/difference_type.hpp>

namespace boost
{
    
    template< class Range > 
    class sub_range : public iterator_range< BOOST_DEDUCED_TYPENAME result_iterator_of<Range>::type > 
    {
		
        typedef BOOST_DEDUCED_TYPENAME result_iterator_of<Range>::type iterator_t;
        typedef iterator_range< iterator_t  > base;
        
    public:
        using base::iterator;
        using base::const_iterator;
        using base::value_type;
        typedef BOOST_DEDUCED_TYPENAME difference_type_of<Range>::type difference_type;
        typedef BOOST_DEDUCED_TYPENAME size_type_of<Range>::type size_type;

    public:
        template< class Range2 >
        sub_range( Range2& r ) : base( r )
        { }
        
        template< class Range2 >
        sub_range( const Range2& r ) : base( r )
        { }

        template< class Iter >
        sub_range( Iter first, Iter last ) :
            base( first, last )
        { }
        
        template< class Range2 >
        sub_range& operator=( Range2& r )
        {
            base::operator=( r );
            return *this;
        }

        template< class Range2 >
        sub_range& operator=( const Range2& r )
        {
            base::operator=( r );
            return *this;
        }
        
        size_type size() const
        {
            return base::size();
        }
		

    };
        
} // namespace 'boost'

#endif
