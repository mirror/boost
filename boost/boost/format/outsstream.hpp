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


//---- The stringstream way -------------------------------------------------


// ---   class basic_outsstream -------------------------------------------------
    template<class Ch, class Tr = std::char_traits<Ch> >
    class basic_outsstream : private std::basic_stringbuf<Ch, Tr>, 
                             public BOOST_IO_STD basic_ostream<Ch, Tr>
    // derived from stringbuf to access pbase(), pptr() & co  (and uses the buffer)
    // publicly derived from basic_ostream to make this class a stream.
    {
        typedef std::basic_stringbuf<Ch, Tr> buff_t;
        typedef BOOST_IO_STD basic_ostream<Ch, Tr> stream_t;
    public:
        typedef std::basic_string<Ch,Tr>     string_type;
        using stream_t::getloc;  // also in buff_t:: 

        basic_outsstream() : std::basic_stringbuf<Ch,Tr>(),
                             std::basic_ostream<Ch,Tr>(this) {}

        // buffer access via strings
        string_type str()     const { return buff_t::str(); }  // [begin, end[
        string_type cur_str() const { return string_type(str(), 0, pcount()); } // [begin, cur[
        string_type p_str() const { return string_type(begin(), cur()); } // [begin, cur[

        // copy-less access (note the pointers can be invalidated when modifying the stream)
        std::streamsize pcount() const { return cur() - begin(); }
        const Ch * begin() const { return buff_t::pbase(); } 
        const Ch * cur()   const { return buff_t::pptr(); } 
        const Ch * end()   const { return buff_t::epptr(); }

        void clear_buffer();
    };

#else // BOOST_NO_STRINGSTREAM


//---- The strstream way -------------------------------------------------

    template <class Ch, 
#if !( BOOST_WORKAROUND(__GNUC__, <3) &&  defined(__STL_CONFIG_H) )
        class Tr = std::char_traits<Ch> > 
#else
    class Tr = std::string_char_traits<Ch> > 
#endif
    class basic_outsstream; // we define only the <char> specialisaton

// ---   class basic_outsstream -------------------------------------------------
    template<class Tr>
    class basic_outsstream<char, Tr> : private BOOST_IO_STD  strstreambuf, 
                                       public std::basic_ostream<char, Tr>
    {
    public:
        typedef char Ch;
        typedef std::basic_string<Ch,Tr>      string_type;
        typedef BOOST_IO_STD strstreambuf     buff_t;
        typedef std::basic_ostream<char, Tr>  stream_t;
    public:
        basic_outsstream();

        // ! physically copy chars :
        string_type str(); 
        string_type cur_str() const  { return string_type(begin(), cur());  } 

        int freeze() const { return buff_t::freeze(); }
        void freeze(int x) { buff_t::freeze(x); }

        // copy-less access (be careful, the pointer are invalidated when modifying the stream) :
        std::streamsize pcount() const { return cur()-begin(); }
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
