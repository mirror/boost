// -*- C++ -*-
//  Boost  format   ----------------------------------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2003
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// ------------------------------------------------------------------------------
//   outsstream<Ch, Tr>   is  a class extending stringstream by adding :
//     clear_buffer() method, and
//     access to the [pbase(), pptr()[ part of the 'output sequence' 
//     (see §27.5.1 of the C++ standard)
//     if sstream is not available, it uses strstream and is slightly different.
// ------------------------------------------------------------------------------

#ifndef BOOST_FORMAT_OUTSSTREAM_H
#define BOOST_FORMAT_OUTSSTREAM_H

#include <boost/assert.hpp>
#include <boost/format/detail/config_macros.hpp>

#if !defined( BOOST_NO_STRINGSTREAM)  & ! BOOST_WORKAROUND(__GNUC__, <3)
#include <sstream>
#else
#include <strstream>
#include <string>
#endif // BOOST_NO_STRING_STREAM


namespace boost {
namespace io {

#if !defined( BOOST_NO_STRINGSTREAM)  & ! BOOST_WORKAROUND(__GNUC__, <3)

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_outsstream : private std::basic_stringbuf<Ch, Tr>, 
                         public BOOST_IO_STD basic_ostream<Ch, Tr>
    // derived from stringbuf to access pbase(), pptr() & co  (and uses the buffer)
   // publicly derived from basic_ostream to make this class a stream.
{
  typedef std::basic_string<Ch,Tr>     string_t;
  typedef std::basic_stringbuf<Ch, Tr> buff_t;
public:
  basic_outsstream() : std::basic_stringbuf<Ch,Tr>(),
                       std::basic_ostream<Ch,Tr>(this) {}
  string_t cur_str()  const { return string_t(begin(), cur());  } // ! physically copy chars
  string_t full_str() const { return string_t(begin(), end());; }
  string_t str()      const { return buff_t::str(); }

  // copy-less access (be careful, the pointer are invalidated when modifying the stream) :
  std::streamsize pcount() const { return buff_t::pptr() - buff_t::pbase(); }
  const Ch * begin() const { return buff_t::pbase(); } 
  const Ch * cur()   const { return buff_t::pptr(); } 
  const Ch * end()   const { return buff_t::epptr(); }

  void clear_buffer();
};




#else // BOOST_NO_STRINGSTREAM

template <class Ch, 
#if ! defined( __STL_CONFIG_H )  // typically gcc < 3
          class Tr = std::char_traits<Ch> > 
#else
          class Tr = std::string_char_traits<Ch> > 
#endif
class basic_outsstream;

template<class Tr>
class basic_outsstream<char, Tr> : private BOOST_IO_STD  strstreambuf, 
                                   public std::basic_ostream<char, Tr>
{
public:
  typedef char Ch;
  typedef std::basic_string<Ch,Tr>      string_t;
  typedef BOOST_IO_STD strstreambuf     buff_t;
  typedef std::basic_ostream<char, Tr>  stream_t;
public:
  basic_outsstream();

  // ! physically copy chars :
  string_t str(); 
  string_t cur_str() const  { return string_t(begin(), cur());  } 
  string_t full_str() const { return string_t(begin(), end());  }

  int freeze() const { return buff_t::freeze(); }
  void freeze(int x) { buff_t::freeze(x); }

  // copy-less access (be careful, the pointer are invalidated when modifying the stream) :
  std::streamsize pcount() const { return (buff_t::pptr()-buff_t::pbase()); }
  const Ch * begin() const { return buff_t::pbase(); } 
  const Ch * cur()   const { return buff_t::pptr(); } 
  const Ch * end()   const { return buff_t::epptr(); }

  void clear_buffer();
};
  
#endif // BOOST_NO_STRINGSTREAM


typedef basic_outsstream<char> outsstream;

} // namespace boost::io
} // namespace boost


#include <boost/format/outsstream_impl.hpp> // implementation

#endif // BOOST_FORMAT_OUTSSTREAM_H include guard
