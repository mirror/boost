/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_iarchive_impl.cpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <cstdlib> // mbtowc
#include <cstring> // memcpy
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::memcpy; 
    using ::mbtowc;
} // namespace std
#endif

#include <boost/detail/workaround.hpp> // RogueWave and Dinkumware
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, == 1)
#include <boost/archive/dinkumware.hpp>
#endif

#include <boost/throw_exception.hpp>

#include <boost/archive/archive_exception.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include "basic_xml_grammar.hpp"

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// implemenations of functions specific to char archives

template<class Archive>
void xml_iarchive_impl<Archive>::load(std::string &s){
    bool result = gimpl->parse_string(is, s);
    if(! result)
        boost::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
}

#ifndef BOOST_NO_STD_WSTRING
template<class Archive>
void xml_iarchive_impl<Archive>::load(std::wstring &ws){
    std::string s;
    bool result = gimpl->parse_string(is, s);
    if(! result)
        boost::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
    
    #if BOOST_WORKAROUND(_RWSTD_VER, BOOST_TESTED_AT(20101))
    if(NULL != ws.data())
    #endif
        ws.resize(0);
    const char * start = s.data();
    const char * end = start + s.size();
    while(start < end){
        wchar_t wc;
        int result = std::mbtowc(&wc, start, end - start);
        if(0 < result){
            start += result;
            ws += wc;
            continue;
        }
        boost::throw_exception(
            iterators::dataflow_exception(
                iterators::dataflow_exception::invalid_conversion
            )
        );
    }
}
#endif

template<class Archive>
void xml_iarchive_impl<Archive>::load(char * s){
    std::string tstring;
    bool result = gimpl->parse_string(is, tstring);
    if(! result)
        boost::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
    std::memcpy(s, tstring.data(), tstring.size());
    s[tstring.size()] = 0;
}

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<class Archive>
void xml_iarchive_impl<Archive>::load(wchar_t * ws){
    std::string s;
    bool result = gimpl->parse_string(is, s);
    if(! result)
        boost::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
        
    const char * start = s.data();
    const char * end = start + s.size();
    while(start < end){
        wchar_t wc;
        int result = std::mbtowc(&wc, start, end - start);
        if(0 < result){
            start += result;
            *ws++ = wc;
            continue;
        }
        boost::throw_exception(
            iterators::dataflow_exception(
                iterators::dataflow_exception::invalid_conversion
            )
        );
    }
    *ws = L'\0';
}
#endif

template<class Archive>
void xml_iarchive_impl<Archive>::load_override(class_name_type & t, int){
    const std::string & s = gimpl->rv.class_name;
    if(s.size() > BOOST_SERIALIZATION_MAX_KEY_SIZE - 1)
        boost::throw_exception(archive_exception::invalid_class_name);
    char * tptr = t;
    std::memcpy(tptr, s.data(), s.size());
    tptr[s.size()] = '\0';
}

template<class Archive>
void xml_iarchive_impl<Archive>::init(){
    gimpl->init(is);
    header = true;
}

template<class Archive>
xml_iarchive_impl<Archive>::xml_iarchive_impl(
    std::istream &is_,
    unsigned int flags
) :
    basic_text_iprimitive<std::istream>(
        is_, 
        0 != (flags & no_codecvt)
    ),
    basic_xml_iarchive<Archive>(flags),
    gimpl(new xml_grammar())
{
    if(0 == (flags & no_header))
        init();
}

template<class Archive>
xml_iarchive_impl<Archive>::~xml_iarchive_impl(){
    if(header)
        gimpl->windup(is);
    delete gimpl;
}
} // namespace archive
} // namespace boost
