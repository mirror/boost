// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

#include <boost/range/functions.hpp >
#include <boost/range/metafunctions.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

namespace
{
    
    //
    // example: extrating bounds in a generic algorithm
    //
    template< typename Range, typename T >
    inline typename boost::iterator_of<Range>::type
    find( Range& c, const T& value )
    {
       return std::find( boost::begin( c ), boost::end( c ), value );
    }
    
    template< typename Range, typename T >
    inline typename boost::const_iterator_of<Range>::type 
    find( const Range& c, const T& value )
    {
       return std::find( boost::begin( c ), boost::end( c ), value );
    }
                   
    // 
    // replace first value and return its index
    //                                
    template< class Range, class T >
    inline typename boost::size_type_of< Range >::type
    my_generic_replace( Range& c, const T& value, const T& replacement )
    {
       typename boost::iterator_of<Range>::type found = find( c, value );
       
       if( found != boost::end( c ) )
           *found = replacement;
       return std::distance( boost::begin( c ), found );
    }                  
}


int main()
{
    //
    // usage
    //
    const int N = 5;                     
    std::vector<int> my_vector;
    int values[] = { 1,2,3,4,5,6,7,8,9 };
    my_vector.assign( values, values + 9 );
    typedef std::vector<int>::iterator iterator;
    std::pair<iterator,iterator>       my_view( boost::begin( my_vector ), 
                                                boost::begin( my_vector ) + N );
    char  str_val[] = "a string";
    char* str       = str_val;
    
    std::cout << my_generic_replace( my_vector, 4, 2 )
              << my_generic_replace( my_view, 4, 2 )
              << my_generic_replace( str, 'a', 'b' );
    return 0;
}
