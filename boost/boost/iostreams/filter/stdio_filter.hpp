// (C) Copyright Jonathan Turkanis 2005.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Based on the work of Christopher Diggins.

#ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif
                       
#include <iostream>
#include <memory>    // allocator.
#include <vector> 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/one_step_filter.hpp>
#include <boost/iostreams/pipeline.hpp>      
#include <boost/iostreams/streambuf_facade.hpp>

namespace boost { namespace iostreams {

namespace detail {

} // End namespace detail.

template<typename Ch, typename Alloc = std::allocator<Ch> >
class basic_stdio_filter : public one_step_filter<Ch, Alloc> {
private:
    typedef one_step_filter<Ch, Alloc>       base_type;
public:
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::category     category;
    typedef typename base_type::vector_type  vector_type;
private:
    static std::istream& standard_input(char*) { return std::cin; }
    static std::ostream& standard_output(char*) { return std::cout; }
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    static std::wistream& standard_input(wchar_t*) { return std::wcin; }
    static std::wostream& standard_output(wchar_t*) { return std::wcout; }
#endif // BOOST_IOSTREAMS_NO_WIDE_STREAMS

    struct scoped_redirector { // Thanks to Maxim Egorushkin.
        scoped_redirector( std::basic_ios<Ch>& ios,
                           std::basic_streambuf<Ch>* newbuf )
            : ios_(ios), old_(ios.rdbuf(newbuf)) 
            { }
        ~scoped_redirector() { ios_.rdbuf(old_); }
        std::basic_ios<Ch>&        ios_;
        std::basic_streambuf<Ch>*  old_;
    };

    virtual void do_filter() = 0;
    virtual void do_filter(const vector_type& src, vector_type& dest)
    {
        streambuf_facade< basic_array_source<Ch> >           
                          srcbuf(&src[0], &src[0] + src.size());
        streambuf_facade< back_insert_device<vector_type> >  
                          destbuf(iostreams::back_inserter(dest));
        scoped_redirector redirect_input(standard_input((Ch*)0), &srcbuf);
        scoped_redirector redirect_output(standard_output((Ch*)0), &destbuf);
        do_filter();
    }
};
BOOST_IOSTREAMS_PIPABLE(basic_stdio_filter, 2)

typedef basic_stdio_filter<char>     stdio_filter;
typedef basic_stdio_filter<wchar_t>  wstdio_wfilter;

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_STDIO_FILTER_HPP_INCLUDED
