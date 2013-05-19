
//  (C) Copyright Edward Diener 2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_LAMBDA_HPP)
#define BOOST_TTI_DETAIL_LAMBDA_HPP

#include <boost/mpl/or.hpp>
#include <boost/tti/detail/dmetafunc.hpp>
#include <boost/tti/detail/dplaceholder.hpp>
#include <boost/tti/gen/namespace_gen.hpp>

namespace boost
  {
  namespace tti
    {
    namespace detail
      {
      template <class TTI_T>
      struct is_lambda_expression :
        boost::mpl::or_
          <
          BOOST_TTI_NAMESPACE::detail::is_metafunction_class<TTI_T>,
          BOOST_TTI_NAMESPACE::detail::is_placeholder_expression<TTI_T>
          >
        {
        };
      }
    }
  }
  
#endif // BOOST_TTI_DETAIL_LAMBDA_HPP
