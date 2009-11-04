/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library

    Global application configuration
    
    http://www.boost.org/

    Copyright (c) 2001-2009 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(BOOST_SPIRIT_PATTERN_PARSER_HPP)
#define BOOST_SPIRIT_PATTERN_PARSER_HPP

#include <boost/spirit/include/classic_primitives.hpp>
#include <boost/wave/wave_config.hpp>

// this must occur after all of the includes and before any code appears
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_PREFIX
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace util {

    ///////////////////////////////////////////////////////////////////////////
    //
    //  pattern_and class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT = char, typename Pattern = unsigned long>
    struct pattern_and 
      : public boost::spirit::classic::char_parser<pattern_and<CharT> >
    {
        pattern_and(CharT pattern_, Pattern pattern_mask_ = Pattern())
        :   pattern(pattern_), 
            pattern_mask((Pattern() != pattern_mask_) ? pattern_mask_ : Pattern(pattern_))
        {}

        template <typename T>
        bool test(T pattern_) const
        { return ((Pattern)pattern_ & pattern_mask) == (Pattern)pattern; }

        CharT   pattern;
        Pattern pattern_mask;
    };

    template <typename CharT, typename Pattern>
    inline pattern_and<CharT, Pattern>
    pattern_p(CharT pattern, Pattern pattern_mask = Pattern())
    { return pattern_and<CharT, Pattern>(pattern, pattern_mask); }

///////////////////////////////////////////////////////////////////////////////
}   // namespace util
}   // namespace wave
}   // namespace boost

// the suffix header occurs after all of the code
#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // defined(BOOST_SPIRIT_PATTERN_PARSER_HPP)
