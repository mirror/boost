
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_template_cp.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  
#if defined(BOOST_TTI_VERSION_1_6)

  // TemplateNotExist does not exist at all
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TEMPLATE_GEN(TemplateNotExist)<AType>));
  
#else

  // TemplateNotExist does not exist at all
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist)<AType>));
  
#endif

  return 0;

  }
