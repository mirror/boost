// (C) Copyright Jonathan Turkanis 2003.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED
#define BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode.
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace iostreams {

//--------------Definitions of helper templates for device concepts-----------//

template<typename Mode, typename Ch = char>
struct device {
    typedef Ch char_type;
    struct io_category
        : Mode,
          device_tag,
          closable_tag,
          localizable_tag
        { };

    void close()
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    }

    void close(BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((is_convertible<Mode, two_sequence>::value));
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wdevice : device<Mode, Ch> { };

typedef device<input>    source;
typedef device<output>   sink;
typedef wdevice<input>   wsource;
typedef wdevice<output>  wsink;

//--------------Definitions of helper templates for simple filter concepts----//

template<typename Mode, typename Ch = char>
struct filter {
    typedef Ch char_type;
    struct io_category
        : Mode,
          filter_tag,
          closable_tag,
          localizable_tag
        { };

    template<typename Device>
    void close(Device&)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((!is_convertible<Mode, two_sequence>::value));
    }

    template<typename Device>
    void close(Device&, BOOST_IOS::openmode)
    {
        using namespace detail;
        BOOST_STATIC_ASSERT((is_convertible<Mode, two_sequence>::value));
    }

    template<typename Locale>
    void imbue(const Locale&) { }
};

template<typename Mode, typename Ch = wchar_t>
struct wfilter : filter<Mode, Ch> { };

typedef filter<input>    input_filter;
typedef filter<output>   output_filter;
typedef wfilter<input>   input_wfilter;
typedef wfilter<output>  output_wfilter;
        
//------Definitions of helper templates for multi-character filter cncepts----//

template<typename Mode, typename Ch = char>
struct multichar_filter : filter<Mode, Ch> {
    struct io_category : filter<Mode, Ch>::io_category, multichar_tag { };
};

template<typename Mode, typename Ch = wchar_t>
struct multichar_wfilter : multichar_filter<Mode, Ch> { };

typedef multichar_filter<input>    multichar_input_filter;
typedef multichar_filter<output>   multichar_output_filter;
typedef multichar_wfilter<input>   multichar_input_wfilter;
typedef multichar_wfilter<output>  multichar_output_wfilter;

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_CONCEPTS_HPP_INCLUDED
