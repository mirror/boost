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
  *   FILE         regex_grep.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Provides regex_grep implementation.
  */

#ifndef BOOST_REGEX_V4_REGEX_GREP_HPP
#define BOOST_REGEX_V4_REGEX_GREP_HPP


namespace boost{

#ifdef __BORLANDC__
   #pragma option push -a8 -b -Vx -Ve -pc  -w-8037
#endif


//
// regex_grep:
// find all non-overlapping matches within the sequence first last:
//
template <class Predicate, class BidiIterator, class charT, class traits, class Allocator>
inline unsigned int regex_grep(Predicate foo, 
                               BidiIterator first, 
                               BidiIterator last, 
                               const reg_expression<charT, traits, Allocator>& e, 
                               match_flag_type flags = match_default)
{
   if(e.flags() & regex_constants::failbit)
      return false;
   typedef          detail::rebind_allocator<sub_match<BidiIterator>, Allocator>  binder;
   typedef typename binder::type                                                  match_allocator_type;
   //typedef Allocator match_allocator_type;

   match_results<BidiIterator, match_allocator_type> m;
   re_detail::perl_matcher<BidiIterator, match_allocator_type, traits, Allocator> matcher(first, last, m, e, flags);
   unsigned int count = 0;
   while(matcher.find())
   {
      ++count;
      if(0 == foo(m))
         return count; // caller doesn't want to go on
      if(m[0].second == last)
         return count; // we've reached the end, don't try and find an extra null match.
      if(m.length() == 0)
      {
         // we found a NULL-match, now try to find
         // a non-NULL one at the same position:
         BidiIterator last_end(m[0].second);
         if(last_end == last)
            return count;
         matcher.setf(match_not_null | match_continuous);
         if(matcher.find())
         {
            ++count;
            last_end = m[0].second;
            if(0 == foo(m))
               return count;
         }
         else
         {
            // reset match back to where it was:
            m.set_second(last_end);
         }
         matcher.unsetf((match_not_null | match_continuous) & ~flags);
      }
   }
   return count;
}

//
// regex_grep convenience interfaces:
#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
//
// this isn't really a partial specialisation, but template function
// overloading - if the compiler doesn't support partial specialisation
// then it really won't support this either:
template <class Predicate, class charT, class Allocator, class traits>
inline unsigned int regex_grep(Predicate foo, const charT* str, 
                        const reg_expression<charT, traits, Allocator>& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + traits::length(str), e, flags);
}

template <class Predicate, class ST, class SA, class Allocator, class charT, class traits>
inline unsigned int regex_grep(Predicate foo, const std::basic_string<charT, ST, SA>& s, 
                 const reg_expression<charT, traits, Allocator>& e, 
                 match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}
#else  // partial specialisation
inline unsigned int regex_grep(bool (*foo)(const cmatch&), const char* str, 
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + regex::traits_type::length(str), e, flags);
}
#ifndef BOOST_NO_WREGEX
inline unsigned int regex_grep(bool (*foo)(const wcmatch&), const wchar_t* str, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, str, str + wregex::traits_type::length(str), e, flags);
}
#endif
inline unsigned int regex_grep(bool (*foo)(const match_results<std::string::const_iterator>&), const std::string& s,
                        const regex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}
#if !defined(BOOST_NO_WREGEX)
inline unsigned int regex_grep(bool (*foo)(const match_results<std::basic_string<wchar_t>::const_iterator>&), 
                     const std::basic_string<wchar_t>& s, 
                        const wregex& e, 
                        match_flag_type flags = match_default)
{
   return regex_grep(foo, s.begin(), s.end(), e, flags);
}
#endif
#endif

#ifdef __BORLANDC__
  #pragma option pop
#endif

} // namespace boost

#endif  // BOOST_REGEX_V4_REGEX_GREP_HPP
