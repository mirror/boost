// -*- C++ -*-
//  Boost general library 'format'   ---------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2003
//                  krempp@crans.ens-cachan.fr
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

/*  outsstream<Ch, Tr>   is  a class extending stringstream by adding :
    clear_buffer() method, and
    access to the [pbase(), pptr()[ part of the 'output sequence' 
    (see §27.5.1 of the C++ standard)
    
    if sstream is not available, it uses strstream and is slightly different.
*/

#ifndef BOOST_FORMAT_OUTSSTREAM_H
#define BOOST_FORMAT_OUTSSTREAM_H

#ifndef BOOST_NO_STRINGSTREAM
#include <sstream>
#else
#include <strstream>
#include <string>
#endif

#include <boost/assert.hpp>


namespace boost {
namespace io {

#ifndef BOOST_NO_STRINGSTREAM  // g++ 2.95 might fail there, see boost/config/stdlib/sgi.hpp

template<class Ch, class Tr = std::char_traits<Ch> >
class basic_outsstream : private std::basic_stringbuf<Ch, Tr>, 
                         public BOOST_IO_STD basic_ostream<Ch, Tr>
{
  typedef std::basic_string<Ch,Tr>     string_t;
  typedef std::basic_stringbuf<Ch, Tr> buff_t;
public:

  basic_outsstream() : std::basic_stringbuf<Ch,Tr>(), 
                       std::basic_ostream<Ch,Tr>(this) {}
  
  string_t str() const { return string_t(begin(), cur());  } // ! physically copy chars
  string_t full_str() const { return buff_t::str(); }

  // copy-less access (be careful, the pointer are easily invalidated ) :
  std::streamsize pcount() const { return (pptr()-pbase()); }
  const Ch * begin() const { return pbase(); } 
  const Ch * cur()   const { return pptr(); } 
  const Ch * end()   const { return epptr(); }

  void clear_buffer() { 
    const Ch * p = pptr();
    const Ch * b = pbase();
    if(p != NULL && p != b) {
      typedef typename Tr::pos_type pos_type;
      pos_type pos = seekpos(0, std::ios_base::out); 
      BOOST_ASSERT( pos != pos_type(std::streamoff(-1)) ); 
    }
  }
};
  
typedef basic_outsstream<char> outsstream;


#else // BOOST_NO_STRINGSTREAM

template <class Ch, 
#if ! defined( __STL_CONFIG_H )  // typically gcc < 3
          class Tr = std::char_traits<Ch> > 
#else
          class Tr = std::string_char_traits<Ch> > 
#endif
class basic_outsstream;

template<class Tr>
class basic_outsstream<char, Tr> : private BOOST_IO_STD strstreambuf, 
                                   public std::basic_ostream<char, Tr>
{
public:
  typedef char Ch;
  typedef std::basic_string<Ch,Tr>     string_t;
//   typedef std::basic_stringbuf<Ch, Tr> buff_t;

  basic_outsstream() : BOOST_IO_STD strstreambuf(), 
                       std::basic_ostream<Ch,Tr>( this)   {}
  
   string_t str() const {  return string_t(begin(), cur());  } // ! physically copy chars
   string_t full_str() const { return string_t(begin(), end());  }

  // copy-less access  (be careful, the pointer are easily invalidated) :
  std::streamsize pcount() const { return (pptr()-pbase()); }
  const Ch * begin() const { return pbase(); } 
  const Ch * cur()   const { return pptr(); } 
  const Ch * end()   const { return epptr(); }

  void clear_buffer() {   
    freeze(false);
    const Ch * p = pptr();
    const Ch * b = pbase();
    if(p != NULL && p != b) {
      seekpos(0, std::ios_base::out); 
    }
    freeze(false);
  }
};
  
typedef basic_outsstream<char> outsstream;

#endif // BOOST_NO_STRINGSTREAM

} // namespace boost::io
} // namespace boost


#endif // BOOST_FORMAT_OUTSSTREAM_H include guard
