//  (C) Copyright Steve Cleary & John Maddock 2000.
//  Use, modification and distribution is subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version including documentation.

#include <boost/static_assert.hpp>

//
// this tests should fail:
//

struct Bob
{
  private:  // can be in private, to avoid namespace pollution
    BOOST_STATIC_ASSERT(sizeof(int) == sizeof(char)); // will not compile
  public:

  // Member function scope: provides access to member variables
  int x;
  char c;
  int f()
  {
#ifndef _MSC_VER // broken sizeof in VC6
    BOOST_STATIC_ASSERT(sizeof(x) == 4);
    BOOST_STATIC_ASSERT(sizeof(c) == 1);
#endif
    //BOOST_STATIC_ASSERT((sizeof(x) == sizeof(c))); // should not compile
    return x;
  }
};






