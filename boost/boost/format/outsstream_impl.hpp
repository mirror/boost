// -*- C++ -*-
//  Boost  format   ----------------------------------------------------
//  See http://www.boost.org for updates, documentation, and revision history.

//  (C) Samuel Krempp 2003
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

// ------------------------------------------------------------------------------
// implementation included by outsstream.hpp.
// ------------------------------------------------------------------------------

namespace boost {
namespace io {

#if !defined( BOOST_NO_STRINGSTREAM)  & ! BOOST_WORKAROUND(__GNUC__, <3)

template<class Ch, class Tr >
void
basic_outsstream<Ch, Tr>:: clear_buffer() { 
    const Ch * p = pptr();
    const Ch * b = pbase();
    if(p != NULL && p != b) {
      typedef typename Tr::pos_type pos_type;
      pos_type pos = buff_t::seekpos(0, std::ios_base::out); 
      BOOST_ASSERT( pos != pos_type(std::streamoff(-1)) ); 
    }
}



#else // BOOST_NO_STRINGSTREAM


template <class Tr>
basic_outsstream<char,Tr> ::basic_outsstream() : 
  buff_t(),  
  stream_t(this) 
{ 
  stream_t::init(this);  // the strem construction isnt enough with gcc-2.95
}  
  

template <class Tr>
basic_string<char, Tr> 
basic_outsstream<char, Tr> ::str() {   // ! physically copy chars :
    string_t s(buff_t::str(), pcount());
    freeze(false);
    return s;
}

template<class Tr >
void
basic_outsstream<char, Tr>:: clear_buffer() { 
    freeze(false);
    const Ch * p = buff_t::pptr();
    const Ch * b = buff_t::pbase();
    if(p != NULL && p != b) {
      buff_t::seekpos(0, std::ios_base::out); 
    }
    freeze(false);
}

#endif

} //namespace io
} //namespace boost
