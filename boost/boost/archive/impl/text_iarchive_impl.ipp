/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_iarchive_impl.ipp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

//////////////////////////////////////////////////////////////////////
// implementation of basic_text_iprimitive overrides for the combination
// of template parameters used to implement a text_iprimitive

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/detail/workaround.hpp> // RogueWave

#include <boost/archive/text_iarchive.hpp>

namespace boost {
namespace archive {

template<class Archive>
void text_iarchive_impl<Archive>::load(char *s)
{
    std::size_t size;
    * this->This() >> size;
    // skip separating space
    is.get();
    // Works on all tested platforms
    is.read(s, size);
    s[size] = '\0';
}

template<class Archive>
void text_iarchive_impl<Archive>::load(std::string &s)
{
    std::size_t size;
    * this->This() >> size;
    // skip separating space
    is.get();
    // borland de-allocator fixup
    #if BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(20101))
    if(NULL != s.data())
    #endif
        s.resize(size);
    is.read(const_cast<char *>(s.data()), size);
}

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<class Archive>
void text_iarchive_impl<Archive>::load(wchar_t *ws)
{
    std::size_t size;
    * this->This() >> size;
    // skip separating space
    is.get();
    is.read((char *)ws, size * sizeof(wchar_t)/sizeof(char));
    ws[size] = L'\0';
}
#endif

#ifndef BOOST_NO_STD_WSTRING
template<class Archive>
void text_iarchive_impl<Archive>::load(std::wstring &ws)
{
    std::size_t size;
    * this->This() >> size;
    // borland de-allocator fixup
    #if BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(20101))
    if(NULL != ws.data())
    #endif
        ws.resize(size);
    // skip separating space
    is.get();
    is.read((char *)ws.data(), size * sizeof(wchar_t)/sizeof(char));
}

#endif

} // namespace archive
} // namespace boost
