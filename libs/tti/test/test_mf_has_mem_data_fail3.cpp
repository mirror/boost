
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_data.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // Wrong enclosing type
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_data
                      <
                      BOOST_TTI_HAS_MEMBER_DATA_GEN(aMember)<_,_>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<bool> 
                      >
                  ));
  
  return 0;

  }
