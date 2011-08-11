
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_type_ct.hpp"

int main()
  {
  
  // Typedef type does not exist ( BType is a nested type )
  
  BOOST_TTI_HAS_TYPE_GEN(BType)<AType,BType> aVar;
  
  return 0;

  }
