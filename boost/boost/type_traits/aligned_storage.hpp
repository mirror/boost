
//  (C) John Maddock 2005.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED
#define BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED

#include "boost/type_traits/type_with_alignment.hpp"

namespace boost {

template <std::size_t Len, std::size_t Align>
struct aligned_storage
{
   typedef typename type_with_alignment<Align>::type aligned_type;
   struct type{
      union
      {
         char m_buf[Len];
         aligned_type m_align;
      };
   };
};

} // namespace boost


#endif // BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED
