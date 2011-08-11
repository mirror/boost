
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_DETAIL_TSELF_HPP)
#define TTI_DETAIL_TSELF_HPP

namespace boost
  {
  namespace tti
    {
    namespace detail
      {
      template <class T>
      struct tself : T
        {
        };
      }
    }
  }
  
#endif // TTI_DETAIL_TSELF_HPP
