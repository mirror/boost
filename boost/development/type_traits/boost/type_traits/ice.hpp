
//  (C) Copyright John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  macros and helpers for working with integral-constant-expressions.

#ifndef BOOST_ICE_TYPE_TRAITS_HPP
#define BOOST_ICE_TYPE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
#define BOOST_DECL_MC(type, name, value) enum{name = value }
#define BOOST_DECL_MC2(type, name, v1, v2) enum{name = v1,v2 }
#else
#define BOOST_DECL_MC(type, name, value) static const type name = value
#define BOOST_DECL_MC2(type, name, v1, v2) static const type name = v1,v2
#endif


namespace boost{
namespace type_traits{

typedef char yes_type;
typedef double no_type;

template <bool b>
struct ice_not
{ BOOST_DECL_MC(bool, value, true); };
template <>
struct ice_not<true>
{ BOOST_DECL_MC(bool, value, false); };

template <bool b1, bool b2, bool b3 = false, bool b4 = false, bool b5 = false, bool b6 = false, bool b7 = false>
struct ice_or;
template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_or
{
   BOOST_DECL_MC(bool, value, true);
};
template <>
struct ice_or<false, false, false, false, false, false, false>
{
   BOOST_DECL_MC(bool, value, false);
};

template <bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true>
struct ice_and;
template <bool b1, bool b2, bool b3, bool b4, bool b5>
struct ice_and
{
   BOOST_DECL_MC(bool, value, false);
};
template <>
struct ice_and<true, true, true, true, true>
{
   BOOST_DECL_MC(bool, value, true);
};


} // namespace type_traits

} // namespace boost

#endif // BOOST_ICE_TYPE_TRAITS_HPP



