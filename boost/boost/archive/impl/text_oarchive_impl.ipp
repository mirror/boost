/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// text_oarchive_impl.ipp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

#include <string>
#include <boost/config.hpp>
#include <locale>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
} // namespace std
#endif

#include <boost/archive/wcslen.hpp>
#include <boost/archive/codecvt_null.hpp>
#include <boost/archive/add_facet.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace boost { 
namespace archive {

//////////////////////////////////////////////////////////////////////
// implementation of basic_text_oprimitive overrides for the combination
// of template parameters used to create a text_oprimitive

template<class Archive>
void text_oarchive_impl<Archive>::save(const char * s)
{
    unsigned len = std::ostream::traits_type::length(s);
    *this->This() << len;
    this->This()->newtoken();
    os << s;
}

template<class Archive>
void text_oarchive_impl<Archive>::save(const std::string &s)
{
    unsigned size = s.size();
    *this->This() << size;
    this->This()->newtoken();
    os << s;
}

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<class Archive>
void text_oarchive_impl<Archive>::save(const wchar_t * ws)
{
    std::size_t l = std::wcslen(ws);
    * this->This() << l;
    this->This()->newtoken();
    os.write((const char *)ws, l * sizeof(wchar_t)/sizeof(char));
}
#endif

#ifndef BOOST_NO_STD_WSTRING
template<class Archive>
void text_oarchive_impl<Archive>::save(const std::wstring &ws)
{
    std::size_t l = ws.size();
    * this->This() << l;
    this->This()->newtoken();
    os.write((const char *)(ws.data()), l * sizeof(wchar_t)/sizeof(char));
}
#endif

} // namespace archive
} // namespace boost

