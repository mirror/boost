//  noncopyable.cpp
///
//  (C) Copyright Eric Niebler 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   21 December 2005 : Initial version.
*/

#include <vector>
#include <boost/foreach.hpp>
#include <boost/noncopyable.hpp>

struct noncopy_vector
  : std::vector<int>
  , private boost::noncopyable
{
};

///////////////////////////////////////////////////////////////////////////////
// main
//   
int main( int, char*[] )
{
    noncopy_vector v1;
    BOOST_FOREACH( int & i, v1 ) { (void)i; }

    noncopy_vector const v2;
    BOOST_FOREACH( int const & i, v2 ) { (void)i; }

    return 0;
}
