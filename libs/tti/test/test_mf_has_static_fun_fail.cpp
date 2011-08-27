
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_static_fun.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/tti/mf/mf_has_static_member_function.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // SomeStaticFunction does not exist at all
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      Pickedname<_,_,_>,
                      boost::mpl::identity<AType>,
                      short,
                      boost::mpl::vector
                        <
                        int,
                        long
                        >
                      >
                  ));
  
  return 0;

  }
