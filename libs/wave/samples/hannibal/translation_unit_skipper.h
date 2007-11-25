//  Hannibal: partial C++ grammar to parse C++ type information
//  Copyright (c) 2005-2006 Danny Havenith
// 
//  Boost.Wave: A Standard compliant C++ preprocessor
//  Copyright (c) 2001-2007 Hartmut Kaiser
// 
//  http://www.boost.org/
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HANNIBAL_TRANSLATION_UNIT_SKIPPER_H_INCLUDED)
#define HANNIBAL_TRANSLATION_UNIT_SKIPPER_H_INCLUDED

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>

#include <boost/wave/wave_config.hpp>
#include <boost/wave/token_ids.hpp>
#include <boost/wave/util/pattern_parser.hpp>

///////////////////////////////////////////////////////////////////////////////
struct translation_unit_skipper
:   public boost::spirit::grammar<translation_unit_skipper>
{
    template <typename ScannerT>
    struct definition
    {
        definition(translation_unit_skipper const& /*self*/)
        {
            using namespace boost::spirit;
            using namespace boost::wave;
            using boost::wave::util::pattern_p;
            
            skip
                =   pattern_p(WhiteSpaceTokenType, TokenTypeMask)
                |   pattern_p(EOLTokenType, TokenTypeMask)
                |   pattern_p(EOFTokenType, TokenTypeMask)
                |   comment_p(pattern_p(PPTokenType, TokenTypeMask), 
                              pattern_p(EOLTokenType, TokenTypeMask))
                ;
        }

        boost::spirit::rule<ScannerT> skip;

        boost::spirit::rule<ScannerT> const&
        start() const { return skip; }
    };
};

#endif // HANNIBAL_TRANSLATION_UNIT_SKIPPER_H_INCLUDED
