
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
  
  // Wrong function parameter type
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_static_member_function
                      <
                      BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_GEN(TSFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>,
                      boost::mpl::vector
                        <
                        NameIntType<AnotherType>,
                        double
                        >
                      >
                  ));
  
  return 0;

  }
