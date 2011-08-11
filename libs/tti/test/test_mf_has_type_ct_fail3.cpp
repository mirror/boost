
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_type_ct.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // Wrong typedef type
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(TheInteger)<_,_>,
                      BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>,
                      boost::mpl::identity<long>
                      >
                  ));
  
  return 0;

  }
