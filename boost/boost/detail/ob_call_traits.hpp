//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  Crippled version for crippled compilers:
//  see libs/utility/call_traits.htm
//
#ifndef BOOST_OB_CALL_TRAITS_HPP
#define BOOST_OB_CALL_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifndef BOOST_TYPE_TRAITS_HPP
#include <boost/type_traits.hpp>
#endif

namespace boost{

template <typename T>
struct call_traits
{
   typedef T value_type;
   typedef T& reference;
   typedef const T& const_reference;
   typedef const T& param_type;
};

}

#endif // BOOST_OB_CALL_TRAITS_HPP
