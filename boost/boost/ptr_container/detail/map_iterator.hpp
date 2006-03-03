//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP
#define BOOST_PTR_CONTAINER_MAP_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <utility>

namespace boost
{ 
        template< class I > 
        class ptr_map_iterator : public boost::iterator_adaptor< ptr_map_iterator<I>, I >
        {
            typedef boost::iterator_adaptor< ptr_map_iterator<I>, I > base_type;
            
        public:
            ptr_map_iterator() : base_type()                                 
            { }
            
            explicit ptr_map_iterator( const I& i ) : base_type(i)
            { }

            template< class I2 >
            ptr_map_iterator( const ptr_map_iterator<I2>& r ) 
             : base_type(r.base())
            { }
            

       }; // class 'ptr_map_iterator'

}

#endif
