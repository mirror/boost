/* boost integer_traits.hpp header file
 *
 * Copyright Jens Maurer 2000
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * $Id$
 *
 * Idea by Beman Dawes, Ed Brey, Steve Cleary, and Nathan Myers
 */

#ifndef BOOST_INTEGER_TRAITS_HPP
#define BOOST_INTEGER_TRAITS_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>

// These are an implementation detail and not part of the interface
#include <limits.h>
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
#include <wchar.h>
#endif


namespace boost {
template<class T>
class integer_traits : public std::numeric_limits<T>
{
public:
  BOOST_STATIC_CONSTANT(bool, is_integral = false);
};

namespace detail {
template<class T, T min_val, T max_val>
class integer_traits_base
{
public:
  BOOST_STATIC_CONSTANT(bool, is_integral = true);
  BOOST_STATIC_CONSTANT(T, const_min = min_val);
  BOOST_STATIC_CONSTANT(T, const_max = max_val);
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  The definition is required even for integral static constants
template<class T, T min_val, T max_val>
const T integer_traits_base<T, min_val, max_val>::const_min;

template<class T, T min_val, T max_val>
const T integer_traits_base<T, min_val, max_val>::const_max;
#endif

} // namespace detail

template<>
class integer_traits<bool>
  : public std::numeric_limits<bool>,
    public detail::integer_traits_base<bool, false, true>
{ };

template<>
class integer_traits<char>
  : public std::numeric_limits<char>,
    public detail::integer_traits_base<char, CHAR_MIN, CHAR_MAX>
{ };

template<>
class integer_traits<signed char>
  : public std::numeric_limits<signed char>,
    public detail::integer_traits_base<signed char, SCHAR_MIN, SCHAR_MAX>
{ };

template<>
class integer_traits<unsigned char>
  : public std::numeric_limits<unsigned char>,
    public detail::integer_traits_base<unsigned char, 0, UCHAR_MAX>
{ };

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<>
class integer_traits<wchar_t>
  : public std::numeric_limits<wchar_t>,
#if !defined(__BORLANDC__)
    public detail::integer_traits_base<wchar_t, WCHAR_MIN, WCHAR_MAX>
#else
    // Borland C++ does not have WCHAR_MIN and WCHAR_MAX
    public detail::integer_traits_base<wchar_t, 0, 0xffff>
#endif
{ };
#endif // BOOST_NO_INTRINSIC_WCHAR_T

template<>
class integer_traits<short>
  : public std::numeric_limits<short>,
    public detail::integer_traits_base<short, SHRT_MIN, SHRT_MAX>
{ };

template<>
class integer_traits<unsigned short>
  : public std::numeric_limits<unsigned short>,
    public detail::integer_traits_base<unsigned short, 0, USHRT_MAX>
{ };

template<>
class integer_traits<int>
  : public std::numeric_limits<int>,
    public detail::integer_traits_base<int, INT_MIN, INT_MAX>
{ };

template<>
class integer_traits<unsigned int>
  : public std::numeric_limits<unsigned int>,
    public detail::integer_traits_base<unsigned int, 0, UINT_MAX>
{ };

template<>
class integer_traits<long>
  : public std::numeric_limits<long>,
    public detail::integer_traits_base<long, LONG_MIN, LONG_MAX>
{ };

template<>
class integer_traits<unsigned long>
  : public std::numeric_limits<unsigned long>,
    public detail::integer_traits_base<unsigned long, 0, ULONG_MAX>
{ };

#ifdef ULLONG_MAX
template<>
class integer_traits<long long>
  : public std::numeric_limits<long long>,
    public detail::integer_traits_base<long long, LLONG_MIN, LLONG_MAX>
{ };
template<>
class integer_traits<unsigned long long>
  : public std::numeric_limits<unsigned long long>,
    public detail::integer_traits_base<unsigned long long, 0, ULLONG_MAX>
{ };
#elif defined(ULONG_LONG_MAX)
template<>
class integer_traits<long long>
  : public std::numeric_limits<long long>,
    public detail::integer_traits_base<long long, LONG_LONG_MIN, LONG_LONG_MAX>
{ };
template<>
class integer_traits<unsigned long long>
  : public std::numeric_limits<unsigned long long>,
    public detail::integer_traits_base<unsigned long long, 0, ULONG_LONG_MAX>
{ };
#elif defined(ULONGLONG_MAX)
template<>
class integer_traits<long long>
  : public std::numeric_limits<long long>,
    public detail::integer_traits_base<long long, LONGLONG_MIN, LONGLONG_MAX>
{ };
template<>
class integer_traits<unsigned long long>
  : public std::numeric_limits<unsigned long long>,
    public detail::integer_traits_base<unsigned long long, 0, ULONGLONG_MAX>
{ };
#endif

} // namespace boost

#endif /* BOOST_INTEGER_TRAITS_HPP */
