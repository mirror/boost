// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED
#define BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED

#include <locale>
#include <boost/iostreams/categories.hpp>            
#include <boost/iostreams/detail/assert_convertible.hpp>        

namespace boost { namespace iostreams {
                    
//--------------Definition of offset_filter-----------------------------------//

template<typename Device>
struct offset_filter {
public:
    typedef typename Device::value_type char_type;
    struct category : mode<Device>::Type,
          device_tag,
          closable_tag,
          localizable_tag
        { };
    direct_adapter(const Direct& d);
    std::streamsize read(char_type* s, std::streamsize n);
    void write(const char_type* s, std::streamsize n);
    std::streamoff seek( std::streamoff, std::ios::seekdir,
                         std::ios::openmode = std::ios::in | std::ios::out );
};

//--------------Implementation of helper offset_view--------------------------//

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_OFFSET_HPP_INCLUDED
