/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         regex_format.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides formatting output routines for search and replace
  *                operations.  Note this is an internal header file included
  *                by regex.hpp, do not include on its own.
  */

#ifndef BOOST_REGEX_V4_REGEX_MERGE_HPP
#define BOOST_REGEX_V4_REGEX_MERGE_HPP


namespace boost{

#ifdef __BORLANDC__
   #pragma option push -a8 -b -Vx -Ve -pc  -w-8037
#endif

template <class OutputIterator, class Iterator, class traits, class Allocator, class charT>
inline OutputIterator regex_merge(OutputIterator out,
                         Iterator first,
                         Iterator last,
                         const reg_expression<charT, traits, Allocator>& e, 
                         const charT* fmt, 
                         match_flag_type flags = match_default)
{
   return regex_replace(out, first, last, e, fmt, flags);
}

template <class OutputIterator, class Iterator, class traits, class Allocator, class charT>
inline OutputIterator regex_merge(OutputIterator out,
                         Iterator first,
                         Iterator last,
                         const reg_expression<charT, traits, Allocator>& e, 
                         const std::basic_string<charT>& fmt,
                         match_flag_type flags = match_default)
{
   return regex_merge(out, first, last, e, fmt.c_str(), flags);
}

template <class traits, class Allocator, class charT>
inline std::basic_string<charT> regex_merge(const std::basic_string<charT>& s,
                         const reg_expression<charT, traits, Allocator>& e, 
                         const charT* fmt,
                         match_flag_type flags = match_default)
{
   return regex_replace(s, e, fmt, flags);
}

template <class traits, class Allocator, class charT>
inline std::basic_string<charT> regex_merge(const std::basic_string<charT>& s,
                         const reg_expression<charT, traits, Allocator>& e, 
                         const std::basic_string<charT>& fmt,
                         match_flag_type flags = match_default)
{
   return regex_replace(s, e, fmt, flags);
}

#ifdef __BORLANDC__
  #pragma option pop
#endif

} // namespace boost

#endif  // BOOST_REGEX_V4_REGEX_MERGE_HPP

