/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         sub_match.cpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Declares template class sub_match.
  */

#ifndef BOOST_REGEX_V4_SUB_MATCH_HPP
#define BOOST_REGEX_V4_SUB_MATCH_HPP

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost{

template <class BidiIterator>
struct sub_match : public std::pair<BidiIterator, BidiIterator>
{
   typedef typename re_detail::regex_iterator_traits<BidiIterator>::value_type       value_type;
#if defined(BOOST_NO_STD_ITERATOR_TRAITS) || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
   typedef          std::ptrdiff_t                                                   difference_type;
#else
   typedef typename re_detail::regex_iterator_traits<BidiIterator>::difference_type  difference_type;
#endif
   typedef          BidiIterator                                                     iterator_type;

   bool matched;

   sub_match() : std::pair<BidiIterator, BidiIterator>(), matched(false) {}
   sub_match(BidiIterator i) : std::pair<BidiIterator, BidiIterator>(i, i), matched(false) {}

   operator std::basic_string<value_type> ()const
   {
      return str();
   }
   difference_type BOOST_REGEX_CALL length()const
   {
      difference_type n = boost::re_detail::distance((BidiIterator)this->first, (BidiIterator)this->second);
      return n;
   }
   std::basic_string<value_type> str()const
   {
      std::basic_string<value_type> result;
      std::size_t len = boost::re_detail::distance((BidiIterator)this->first, (BidiIterator)this->second);
      result.reserve(len);
      BidiIterator i = this->first;
      while(i != this->second)
      {
         result.append(1, *i);
         ++i;
      }
      return result;
   }
   int compare(const sub_match& s)const
   {
      if(matched != s.matched)
         return static_cast<int>(matched) - static_cast<int>(s.matched);
      return str().compare(s.str());
   }

   bool operator==(const sub_match& that)const
   { return compare(that) == 0; }
   bool BOOST_REGEX_CALL operator !=(const sub_match& that)const
   { return compare(that) != 0; }
   bool operator<(const sub_match& that)const
   { return compare(that) < 0; }
   bool operator>(const sub_match& that)const
   { return compare(that) > 0; }
   bool operator<=(const sub_match& that)const
   { return compare(that) <= 0; }
   bool operator>=(const sub_match& that)const
   { return compare(that) >= 0; }

#ifdef BOOST_OLD_REGEX_H
   //
   // the following are deprecated, do not use!!
   //
   operator int()const;
   operator unsigned int()const;
   operator short()const
   {
      return (short)(int)(*this);
   }
   operator unsigned short()const
   {
      return (unsigned short)(unsigned int)(*this);
   }
#endif
};

// comparison to std::basic_string<> part 1:
template <class RandomAccessIterator, class traits, class Allocator>
bool operator == (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator != (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator < (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator <= (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator >= (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                  const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) >= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator > (const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s,
                 const sub_match<RandomAccessIterator>& m)
{ return s.compare(m.str()) > 0; }
// comparison to std::basic_string<> part 2:
template <class RandomAccessIterator, class traits, class Allocator>
bool operator == (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator != (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator < (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator > (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator <= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) <= 0; }
template <class RandomAccessIterator, class traits, class Allocator>
bool operator >= (const sub_match<RandomAccessIterator>& m,
                  const std::basic_string<typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type, traits, Allocator>& s)
{ return m.str().compare(s) >= 0; }
// comparison to const charT* part 1:
template <class RandomAccessIterator>
bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s)
{ return m.str().compare(s) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
bool operator == (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) == 0; }
template <class RandomAccessIterator>
bool operator != (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) != 0; }
template <class RandomAccessIterator>
bool operator < (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) > 0; }
template <class RandomAccessIterator>
bool operator > (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) < 0; }
template <class RandomAccessIterator>
bool operator <= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) >= 0; }
template <class RandomAccessIterator>
bool operator >= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const* s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(s) <= 0; }

// comparison to const charT& part 1:
template <class RandomAccessIterator>
bool operator == (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
bool operator != (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
bool operator > (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
bool operator < (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
bool operator >= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
bool operator <= (const sub_match<RandomAccessIterator>& m,
                  typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }
// comparison to const charT* part 2:
template <class RandomAccessIterator>
bool operator == (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) == 0; }
template <class RandomAccessIterator>
bool operator != (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) != 0; }
template <class RandomAccessIterator>
bool operator < (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) > 0; }
template <class RandomAccessIterator>
bool operator > (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) < 0; }
template <class RandomAccessIterator>
bool operator <= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) >= 0; }
template <class RandomAccessIterator>
bool operator >= (typename re_detail::regex_iterator_traits<RandomAccessIterator>::value_type const& s,
                  const sub_match<RandomAccessIterator>& m)
{ return m.str().compare(0, m.length(), &s, 1) <= 0; }

#ifndef BOOST_NO_STD_LOCALE
template <class charT, class traits, class RandomAccessIterator>
std::basic_ostream<charT, traits>&
   operator << (std::basic_ostream<charT, traits>& os,
                const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#else
template <class RandomAccessIterator>
std::ostream& operator << (std::ostream& os,
                           const sub_match<RandomAccessIterator>& s)
{
   return (os << s.str());
}
#endif

#ifdef BOOST_OLD_REGEX_H
namespace re_detail{
template <class BidiIterator, class charT>
int do_toi(BidiIterator i, BidiIterator j, char c, int radix)
{
   std::string s(i, j);
   char* p;
   int result = std::strtol(s.c_str(), &p, radix);
   if(*p)raise_regex_exception("Bad sub-expression");
   return result;
}

//
// helper:
template <class I, class charT>
int do_toi(I& i, I j, charT c)
{
   int result = 0;
   while((i != j) && (isdigit(*i)))
   {
      result = result*10 + (*i - '0');
      ++i;
   }
   return result;
}
}


template <class BidiIterator>
sub_match<BidiIterator>::operator int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)raise_regex_exception("Bad sub-expression");
   int neg = 1;
   if((i != j) && (*i == '-'))
   {
      neg = -1;
      ++i;
   }
   neg *= re_detail::do_toi(i, j, *i);
   if(i != j)raise_regex_exception("Bad sub-expression");
   return neg;
}
template <class BidiIterator>
sub_match<BidiIterator>::operator unsigned int()const
{
   BidiIterator i = first;
   BidiIterator j = second;
   if(i == j)
      raise_regex_exception("Bad sub-expression");
   return re_detail::do_toi(i, j, *first);
}
#endif

} // namespace boost

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif

