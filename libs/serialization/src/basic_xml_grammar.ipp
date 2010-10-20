/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_grammar.ipp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#if (defined _MSC_VER) && (_MSC_VER == 1200)
#  pragma warning (disable : 4786) // too long name, harmless warning
#endif

#include <istream>
#include <algorithm>
#include <boost/config.hpp> // BOOST_DEDUCED_TYPENAME

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

// #include <boost/spirit/core/composite/operators.hpp>
// #include <boost/spirit/core/composite/actions.hpp>
// #include <boost/spirit/core/primitives/numerics.hpp>

#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_action.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_numeric.hpp>
#include <boost/spirit/include/qi_string.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// for head_iterator test
//#include <boost/bind.hpp> 
#include <boost/function.hpp>
#include <boost/serialization/pfto.hpp>

#include <boost/io/ios_state.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/impl/basic_xml_grammar.hpp>
#include <boost/archive/xml_archive_exception.hpp>
#include <boost/archive/basic_xml_archive.hpp>
#include <boost/archive/iterators/xml_unescape.hpp>

using namespace boost::spirit;

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// template code for basic_xml_grammar of both wchar_t and char types

template<class CharType>
bool basic_xml_grammar<CharType>::my_parse(
    IStream & is,
    const rule_t & rule_,
    CharType delimiter
) const {
    if(is.fail()){
        boost::serialization::throw_exception(
            archive_exception(archive_exception::input_stream_error)
        );
    }
    
    boost::io::ios_flags_saver ifs(is);
    is >> std::noskipws;

    std::basic_string<CharType> arg;
    
    CharType val;
    do{
        BOOST_DEDUCED_TYPENAME basic_xml_grammar<CharType>::IStream::int_type
            result = is.get();
        if(is.fail())
            return false;
        val = static_cast<CharType>(result);
        arg += val;
    }
    while(val != delimiter);
    
    // read just one more character.  This will be the newline after the tag
    // this is so that the next operation will return fail if the archive
    // is terminated.  This will permit the archive to be used for debug
    // and transaction data logging in the standard way.
    
    return qi::parse(arg.begin(), arg.end(), rule_);
}

template<class CharType>
bool basic_xml_grammar<CharType>::parse_start_tag(IStream & is){
    rv.class_name.resize(0);
    return my_parse(is, STag);
}

template<class CharType>
bool basic_xml_grammar<CharType>::parse_end_tag(IStream & is) {
    return my_parse(is, ETag);
}

template<class CharType>
bool basic_xml_grammar<CharType>::parse_string(IStream & is, StringType & s){
    rv.contents.resize(0);
    bool result = my_parse(is, content, '<');
    // note: unget caused a problem with dinkumware.  replace with
 // is.unget();
    // putback another delimiter instead
    is.putback('<');
    if(result)
        s = rv.contents;
    return result;
}

template<class CharType>
basic_xml_grammar<CharType>::basic_xml_grammar(){
    init_chset();

    /* [1] S ::= Sch+ */
    S = +(Sch);

    /* [2] Eq ::= !S '=' !S  */
    Eq = !S >> '=' >> !S;

    /* [3] AttributeList ::= (S Attribute)* */
    AttributeList = *(S >> Attribute);
   
    /* [4] STag ::= S? '<' Name AttributeLIst !S '>' */
    STag = -S >> '<' >> Name >> AttributeList >> !S >> '>';

    /* [5] ETag ::= S? "</" Name !S '>' */ 
    ETag = -S >> "</" >> Name >> !S >> '>';

    /* [6] CharData ::= (AnyChar - ("&" | "<"))+ */
    CharData = +(AnyChar - (qi::lit('&') | '<'))
      [phoenix::ref(rv.contents) += qi::_1]
    ;

    /* [7] CharRef ::= ("&#" Digit* ';') | ("&#x" HexDigit* ';') */
    CharRef
      = (qi::lit("&#") >> *Digit[phoenix::ref(rv.contents) += qi::_1] >> ';')
      | ("&#x" >> *HexDigit[phoenix::ref(rv.contents) += qi::_1] >> ';')
    ;

    /* [8] AmpRef ::= "&amp;"    *
     * [9] LTRef ::= "&lt;"      *
     * [a] GTRef ::= "&gt;"      *
     * [b] AposRef ::= "&apos;"  *
     * [c] QuoteRef ::= "&quot;" */
    AmpRef   = qi::lit("&amp;") [phoenix::ref(rv.contents) += '&'];
    LTRef    = qi::lit("&lt;")  [phoenix::ref(rv.contents) += '<'];
    GTRef    = qi::lit("&gt;")  [phoenix::ref(rv.contents) += '>'];
    AposRef  = qi::lit("&apos;")[phoenix::ref(rv.contents) += '\''];
    QuoteRef = qi::lit("&quot;")[phoenix::ref(rv.contents) += '"'];
    
    /* [d] AmpName ::= "&amp;"   *
     * [e] LTName ::= "&lt;"     *
     * [f] GTName ::= "&gt;"     */
    AmpName = qi::lit("&amp;")[phoenix::ref(rv.class_name) += '&'];
    LTName  = qi::lit("&lt;") [phoenix::ref(rv.class_name) += '<'];
    GTName  = qi::lit("&gt;") [phoenix::ref(rv.class_name) += '>'];

    /* [10] Reference ::= AmpRef LTRef GTRef AposRef QuoteRef CharRef */ 
    Reference
      = AmpRef
      | LTRef
      | GTRef
      | AposRef
      | QuoteRef
      | CharRef
    ;

    /* [11] content ::= '<' | (Reference | CharData)+ '<' */
    content = qi::lit('<') | +(Reference | CharData) >> qi::lit('<');

    ClassIDAttribute
      = qi::lit(BOOST_ARCHIVE_XML_CLASS_ID())
      >> *NameChar
      >> Eq
      >> '"'
      >> qi::short_[phoenix::ref(rv.class_id) = qi::_1]
      >> '"'
    ;

    ObjectIDAttribute
      = ( qi::lit(BOOST_ARCHIVE_XML_OBJECT_ID()) 
        | qi::lit(BOOST_ARCHIVE_XML_OBJECT_REFERENCE()) 
        )
      >> *NameChar
      >> Eq
      >> '"'
      >> qi::lit('_')
      >> qi::uint_[phoenix::ref(rv.object_id) = qi::_1]
      >> '"'
    ;
        
    ClassNameChar
      = AmpName
      | LTName
      | GTName
      | (qi::char_ - '"')[phoenix::ref(rv.class_name) += qi::_1]
    ;
    
    ClassName = *ClassNameChar;
    
    ClassNameAttribute
      = qi::lit(BOOST_ARCHIVE_XML_CLASS_NAME()) 
      >> Eq
      >> '"'
      >> ClassName
      >> '"'
    ;

    TrackingAttribute
      = qi::lit(BOOST_ARCHIVE_XML_TRACKING())
      >> Eq
      >> '"'
      >> qi::uint_[phoenix::ref(rv.tracking_level) = qi::_1]
      >> '"'
    ;

    VersionAttribute
      = qi::lit(BOOST_ARCHIVE_XML_VERSION())
      >> Eq
      >> '"'
      >> qi::uint_[phoenix::ref(rv.version) = qi::_1]
      >> '"'
    ;

    UnusedAttribute
      = Name
      >> Eq
      >> '"'
      >> !CharData
      >> '"'
    ;

    Attribute
      = ClassIDAttribute
      | ObjectIDAttribute
      | ClassNameAttribute
      | TrackingAttribute
      | VersionAttribute
      | UnusedAttribute
    ;

    XMLDecl
      =  -S
      >> "<?xml"
      >> S
      >> "version"
      >> Eq
      >> "\"1.0\""
      >> XMLDeclChars
      >> !S
      >> "?>"
    ;

    DocTypeDecl = -S >> "<!DOCTYPE" >> DocTypeDeclChars >> '>';

    SignatureAttribute = qi::lit("signature") >> Eq >> '"' >> Name >> '"';
    
    SerializationWrapper
      =  -S
      >> "<boost_serialization"
      >> S
      >> SignatureAttribute
      >> S
      >> VersionAttribute
      >> !S
      >> '>'
    ;
}

template<class CharType>
void basic_xml_grammar<CharType>::init(IStream & is){
    if(! my_parse(is, XMLDecl))
        boost::serialization::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
    if(! my_parse(is, DocTypeDecl))
        boost::serialization::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
    if(! my_parse(is, SerializationWrapper))
        boost::serialization::throw_exception(
            xml_archive_exception(xml_archive_exception::xml_archive_parsing_error)
        );
    if(! std::equal(rv.class_name.begin(), rv.class_name.end(), BOOST_ARCHIVE_SIGNATURE()))
        boost::serialization::throw_exception(
            archive_exception(archive_exception::invalid_signature)
        );
}

template<class CharType>
void basic_xml_grammar<CharType>::windup(IStream & is){
    if(is.fail())
        return;
    // uh-oh - don't throw exception from code called by a destructor !
    // so just ignore any failure.
    my_parse(is, ETag);
}

} // namespace archive
} // namespace boost
