#ifndef BOOST_SERIALIZATION_IS_ABSTRACT_CLASS_HPP
#define BOOST_SERIALIZATION_IS_ABSTRACT_CLASS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// is_abstract_class.hpp:

// (C) Copyright 2002 Rani Sharoni (rani_sharoni@hotmail.com) and Robert Ramey
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/mpl/bool_fwd.hpp>

// provokes ICE on microsoft VC 7.0 and maybe gcc 3.2
// so make sure its skipped
#define BOOST_TT_IS_ABSTRACT_CLASS_HPP
// #include <boost/type_traits/is_abstract.hpp>

// so default to false until the above is really fixed
namespace boost {
template<class T>
struct is_abstract {
    typedef mpl::bool_<false> type;
    BOOST_STATIC_CONSTANT(bool, value = is_abstract::type::value); 
};
} // namespace boost

// define a macro to make explicit designation of this more transparent
#define BOOST_IS_ABSTRACT(T)                   \
namespace boost {                              \
template<>                                     \
struct is_abstract<T> {                        \
    BOOST_STATIC_CONSTANT(bool, value = true); \
};                                             \
} // namespace boost
/**/

#endif //BOOST_SERIALIZATION_IS_ABSTRACT_CLASS_HPP
