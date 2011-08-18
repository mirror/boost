
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_type_ct.hpp"
#include <boost/tti/gen/trait_gen.hpp>

int main()
  {
  
  // Enclosing type does not exist
  
  TheInteger<AType::EType,double> aVar;
  
  return 0;

  }
