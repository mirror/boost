/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_grammar.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER == 1200)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/impl/basic_xml_grammar.hpp>

#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

using namespace boost::spirit;

#include <boost/config.hpp>

// fixup for borland
// The following code will be put into Boost.Config in a later revision
#if ! defined(__SGI_STL_PORT) \
&& defined(BOOST_RWSTD_VER) && BOOST_RWSTD_VER<=0x020101
#include <string>
namespace std {
    template<>
    inline string & 
    string::replace (
        char * first1, 
        char * last1,
        const char * first2,
        const char * last2
    ){
        replace(first1-begin(),last1-first1,first2,last2-first2,0,last2-first2);
        return *this;
    }
} // namespace std
#endif

namespace boost {
namespace archive {

typedef basic_xml_grammar<char> xml_grammar;

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// specific definitions for char based XML

template<>
void xml_grammar::init_chset(){
    Char     = standard::char_("\x9\xA\xD\x20-\x7f\x80\x81-\xFF"); 
    Letter   = standard::char_("\x41-\x5A\x61-\x7A\xC0-\xD6\xD8-\xF6\xF8-\xFF");
    Digit    = standard::digit;
    HexDigit = standard::xdigit;
    Extender = standard::char_('\xB7');
    Sch      = standard::char_("\x20\x9\xD\xA");
    NameChar = Letter | Digit | standard::char_("._:-") | Extender ;
    AnyChar  = standard::char_;

    DocTypeDeclChars = *(standard::char_ - qi::lit('>'));
    XMLDeclChars = *(standard::char_ - qi::lit("?>"));
    
    Name =
      (
        (Letter | standard::char_('_') | standard::char_(':'))[
          phoenix::ref(rv.object_name) = qi::_1
        ] >>
        *NameChar[phoenix::ref(rv.object_name) += qi::_1]
      )
    ;
}

} // namespace archive
} // namespace boost

#include "basic_xml_grammar.ipp"

namespace boost {
namespace archive {

// explicit instantiation of xml for 8 bit characters
template class basic_xml_grammar<char>;

} // namespace archive
} // namespace boost

