// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/range.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

namespace
{
   template< typename ExternalCollection, typename T >
   inline typename boost::iterator_of<ExternalCollection>::type
   find( ExternalCollection& c, const T& value )
   {
       return std::find( boost::begin( c ), boost::end( c ), value );
   }

   template< typename ExternalCollection, typename T >
   inline typename boost::const_iterator_of<ExternalCollection>::type 
   find( const ExternalCollection& c, const T& value )
   {
       return std::find( boost::begin( c ), boost::end( c ), value );
   }
                   
   // 
   // replace first value and return its index
   //                                
   template< typename EC, typename T >
   inline typename boost::size_type_of< EC >::type
   my_generic_replace( EC& c, const T& value, const T& replacement )
   {
       typename boost::iterator_of<EC>::type found = find( c, value );
       
       if( found != boost::end( c ) )
           *found = replacement;
       return std::distance( boost::begin( c ), found );
   }                  
}



int main()
{
    const int N = 5;                     
    int v[] = { 1,2,3,4,5,6,6,7,8,9 };
    std::vector<int> my_vector;
    my_vector.assign( boost::begin( v ), boost::end( v ) );
    typedef std::vector<int>::iterator iterator;
    std::pair<iterator,iterator>       my_view( boost::begin( my_vector ), 
                                                boost::begin( my_vector ) + N );
    char str[] = "a string";
    
    std::cout << my_generic_replace( my_vector, 4, 2 )
              << my_generic_replace( my_view, 4, 2 )
              << my_generic_replace( str, 'a', 'b' );
    return 0;
}
