
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_type_ct.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/tti/mf/mf_has_type.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // NoOtherType does not exist at all
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<_,_>,
                      boost::mpl::identity<AnotherType>,
                      float
                      >
                  ));
  
  return 0;

  }
