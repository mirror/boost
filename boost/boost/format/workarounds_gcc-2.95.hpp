// -*- C++ -*-
//  Boost general library 'format'   ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2003
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.



#if  BOOST_WORKAROUND(__GNUC__, < 3) & defined(__STL_CONFIG_H) // nothing to do else

// workarounds for gcc < 3.0  :
// . defines a few macros 
// .  supplies  template classes   basic_foo<char, Tr> where gcc only supplies foo :
//     -  basic_ios<char, Tr>        from ios
//     -  basic_ostream<char, Tr>    from ostream
//     -  basic_srteambuf<char, Tr>  from streambuf
// of course, the traits type 'Tr' is not used at all,
//  and you instantiating those template with a char type different than char fails.



#ifndef BOOST_FORMAT_WORKAROUNDS_GCC295_H
#define BOOST_FORMAT_WORKAROUNDS_GCC295_H

#include <iostream>



// *** 
// gcc's simple classes turned into standard-like template classes :

namespace std {


template <class Ch>
class char_traits : public string_char_traits<Ch> {
};
// only problem : gcc's  'string' is a typedef for basic_string<char, string_char_traits<char> >,
// so strings built using char_traits wont match the type 'string'.
// so it's better to use string_char_traits directly.

template <class Ch, class Tr>
class basic_ios;

template <class Tr> 
class basic_ios<char, Tr> : virtual public ios {
public:
  char fill()  const { return ios::fill(); } // gcc returns wchar..
  char fill(char c)  { return ios::fill(c); } // gcc takes wchar..
};

typedef ios ios_base;


template <class Ch, class Tr>
class basic_ostream;

template <class Tr> 
class basic_ostream<char, Tr> : public basic_ios<char, Tr>, public ostream  {
public:
  basic_ostream(streambuf* sb) : ostream(sb) {}
  char widen(char c) { return c; }
  char narrow(char c, char def) { return c; }
};


template <class Ch, class Tr>
class basic_streambuf;

template <class Tr> 
class basic_streambuf<char, Tr> : public streambuf {
};


} // namespace std


#endif // include guard

#endif // if workaround
