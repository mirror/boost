// Copyright Daniel Wallin 2006. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_CAST_060902_HPP
# define BOOST_PARAMETER_CAST_060902_HPP

# include <boost/type_traits/add_reference.hpp>
# include <boost/type_traits/add_const.hpp>

namespace boost { namespace parameter { namespace aux {

# ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

// Handles possible implicit casts. Used by preprocessor.hpp to
// normalize user input.
//
// cast<void*>::execute() is identity
// cast<void*(X)>::execute() is identity
// cast<void(X)>::execute() casts to X
//
// preprocessor.hpp uses this like this:
//
//   #define X(value, predicate)
//      cast<void predicate>::execute(value)
//
//   X(something, *)
//   X(something, *(predicate))
//   X(something, (int))

template <class T>
struct cast;

template <>
struct cast<void*>
{
    template <class U>
    static U& execute(U& value)
    {
        return value;
    }
};

template <class T>
struct cast<void*(T)>
  : cast<void*>
{
};

template <class T>
struct cast<void(T)>
{
    typedef typename boost::add_reference<
        typename boost::add_const<T>::type
    >::type reference;

    static reference const execute(reference value)
    {
        return value;
    }
};

# endif

}}} // namespace boost::parameter::aux

#endif // BOOST_PARAMETER_CAST_060902_HPP

