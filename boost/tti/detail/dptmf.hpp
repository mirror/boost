
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_PTMF_HPP)
#define BOOST_TTI_DETAIL_PTMF_HPP

#include <boost/config.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/function_types/member_function_pointer.hpp>

namespace boost
  {
  namespace tti
    {
    namespace detail
      {
      template
        <
        class T,
        class R,
        class FS,
        class TAG
        >
      struct ptmf_seq
        {
        typedef typename
        boost::function_types::member_function_pointer
          <
          typename
          boost::mpl::push_front
            <
            typename
            boost::mpl::push_front<FS,T>::type,
            R
            >::type,
          TAG
          >::type type;
        };
      }
    }
  }
  
#endif // BOOST_TTI_DETAIL_PTMF_HPP
