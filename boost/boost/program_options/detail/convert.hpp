// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONVERT_HPP_VP_2004_04_28
#define BOOST_CONVERT_HPP_VP_2004_04_28

#include <boost/detail/workaround.hpp>

#include <string>
#include <locale>
// for mbstate_t
#include <cwchar>
#include <stdexcept>

#if BOOST_WORKAROUND(__ICL, <= 700)
#include <wchar.h>
namespace std
{
    using ::mbstate_t;
}    
#endif

namespace boost {

    /** Converts from local 8 bit encoding into wchar_t string using
        the specified locale facet. */
    std::wstring 
    from_8_bit(const std::string& s, 
               const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);

    /** Converts from wchar_t string into local 8 bit encoding into using
        the specified locale facet. */
    std::string 
    to_8_bit(const std::wstring& s, 
             const std::codecvt<wchar_t, char, std::mbstate_t>& cvt);


    /** Converts 's', which is assumed to be in UTF8 encoding, into wide
        string. */
    std::wstring
    from_utf8(const std::string& s);
    
    /** Converts wide string 's' into string in UTF8 encoding. */
    std::string
    to_utf8(const std::wstring& s);

    /** Converts wide string 's' into local 8 bit encoding determined by
        the current locale. */
    std::string
    to_local_8_bit(const std::wstring& s);

    /** Converts 's', which is assumed to be in local 8 bit encoding, into wide
        string. */
    std::wstring
    from_local_8_bit(const std::string& s);

    namespace program_options
    {
        /** Convert the input string into internal encoding used by
            program_options. Presense of this function allows to avoid
            specializing all methods which access input on wchar_t.
        */
        std::string to_internal(const std::string&);
        /** @overload */
        std::string to_internal(const std::wstring&);
    }


  
}

#endif
