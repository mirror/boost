// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif              

#include <boost/iostreams/detail/disable_warnings.hpp> // MSVC.

#include <ios>               // openmode.            
#include <streambuf>                  
#include <boost/config.hpp>  // member template friends.

namespace boost { namespace iostreams { namespace detail {

template<typename Self, typename Ch, typename Tr, typename Alloc, typename Mode>
class chain_base;

template<typename Chain, typename Access, typename Mode> class chainbuf;

#define BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base)              \
    using base::eback; using base::gptr; using base::egptr;           \
    using base::setg; using base::gbump; using base::pbase;           \
    using base::pptr; using base::epptr; using base::setp;            \
    using base::pbump; using base::underflow; using base::pbackfail;  \
    using base::xsgetn; using base::overflow; using base::sputc;      \
    using base::xsputn; using base::sync; using base::seekoff;        \
    using base::seekpos;                                              \
    /**/

template<typename Ch, typename Tr = std::char_traits<Ch> >
class linked_streambuf : public std::basic_streambuf<Ch, Tr> {
protected:
    typedef std::basic_streambuf<Ch> link;
    linked_streambuf() { }

    //----------grant friendship to chain_base and chainbuf-------------------//

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template< typename Self, typename ChT, typename TrT,
              typename Alloc, typename Mode >
    friend class chain_base;
    template<typename Chain, typename Mode, typename Access>
    friend class chainbuf;
#else
    public:
        typedef std::basic_streambuf<Ch, Tr> base;
        BOOST_IOSTREAMS_USING_PROTECTED_STREAMBUF_MEMBERS(base)
#endif
    virtual void set_next(link* /* next */) { }
    virtual void close(std::ios::openmode) = 0;
};
                                    
} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/enable_warnings.hpp> // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_LINKED_STREAMBUF_HPP_INCLUDED
