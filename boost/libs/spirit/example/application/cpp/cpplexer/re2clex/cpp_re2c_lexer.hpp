/*=============================================================================
    A Standard compliant C++ preprocessor

    Re2C based C++ lexer
    
    Copyright (c) 2001-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.

    See Copyright.txt for full copyright notices and acknowledgements.
=============================================================================*/

#if !defined(_CPP_RE2C_LEXER_HPP__B81A2629_D5B1_4944_A97D_60254182B9A8__INCLUDED_)
#define _CPP_RE2C_LEXER_HPP__B81A2629_D5B1_4944_A97D_60254182B9A8__INCLUDED_

#include <string>
#if defined(BOOST_SPIRIT_DEBUG)
#include <iostream>
#endif // defined(BOOST_SPIRIT_DEBUG)

#include <boost/spirit/core.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>

#include "cpplexer/cpp_token_ids.hpp"
#include "cpplexer/cpp_lex_interface.hpp"
#include "cpplexer/re2clex/scanner.h"
#include "cpplexer/re2clex/cpp_re2c_token.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace cpplexer {
namespace re2clex {

///////////////////////////////////////////////////////////////////////////////
// 
//  encapsulation of the re2c based cpp lexer
//
///////////////////////////////////////////////////////////////////////////////

template <typename IteratorT, typename PositionT = boost::spirit::file_position>
class lexer 
{
public:

    typedef char                            char_t;
    typedef Scanner                         base_t;
    typedef lex_token<IteratorT, PositionT> token_t;
    
    lexer(IteratorT const &first, IteratorT const &last, 
        std::string const &fname);
    ~lexer();

    lex_token<IteratorT, PositionT> scan();
    
private:
    static char const *tok_names[];
    
    Scanner scanner;
    std::string filename;
};

///////////////////////////////////////////////////////////////////////////////
// initialize cpp lexer 
template <typename IteratorT, typename PositionT>
inline
lexer<IteratorT, PositionT>::lexer(IteratorT const &first, 
        IteratorT const &last, std::string const &fname) 
:   filename(fname)
{
    memset(&scanner, '\0', sizeof(Scanner));
    scanner.fd = -1;
    scanner.eol_offsets = aq_create();
    scanner.first = scanner.act = (uchar *)&(*first);
    scanner.last = (uchar *)&(*last);
}

template <typename IteratorT, typename PositionT>
inline
lexer<IteratorT, PositionT>::~lexer() 
{
    aq_terminate(scanner.eol_offsets);
    free(scanner.bot);
}

///////////////////////////////////////////////////////////////////////////////
//  get the next token from the input stream
template <typename IteratorT, typename PositionT>
inline lex_token<IteratorT, PositionT> 
lexer<IteratorT, PositionT>::scan()
{
    token_id id = token_id(re2clex::scan(&scanner));
    return lex_token<IteratorT, PositionT>(id, 
                std::string((char const *)scanner.tok, scanner.cur - scanner.tok), 
                PositionT(filename, scanner.line)
           );
}

///////////////////////////////////////////////////////////////////////////////
//   
//  lex_functor
//   
///////////////////////////////////////////////////////////////////////////////
     
template <typename IteratorT, typename PositionT = boost::spirit::file_position>
class lex_functor 
:   public lex_input_interface<typename lexer<IteratorT, PositionT>::token_t>
{    
public:

    //typedef char                                            char_t;
    //typedef std::basic_string<char_t>                       string_t;
    typedef typename lexer<IteratorT, PositionT>::token_t   token_t;
    
    lex_functor(IteratorT const &first, IteratorT const &last, 
            std::string const &fname)
    :   lexer(first, last, fname)
    {}

// get the next token from the input stream
    token_t get()
    { return lexer.scan(); }
    
private:
    lexer<IteratorT, PositionT> lexer;
};

///////////////////////////////////////////////////////////////////////////////
//  
//  The new_lexer_gen<>::new_lexer function (declared in cpp_slex_token.hpp)
//  should be defined inline, if the lex_functor shouldn't be instantiated 
//  separately from the lex_iterator.
//
//  Separate (explicit) instantiation helps to reduce compilation time.
//
///////////////////////////////////////////////////////////////////////////////

#if defined(CPP_SEPARATE_LEXER_INSTANTIATION)
#define RE2C_NEW_LEXER_INLINE
#else
#define RE2C_NEW_LEXER_INLINE inline
#endif 

///////////////////////////////////////////////////////////////////////////////
//
//  The 'new_lexer' function allows the opaque generation of a new lexer object.
//  It is coupled to the token type to allow to decouple the lexer/token 
//  configurations at compile time.
//
//  This function is declared inside the cpp_slex_token.hpp file, which is 
//  referenced by the source file calling the lexer and the sourcefile, which
//  instantiates the lex_functor. But is is defined here, so it will be 
//  instantiated only while compiling the sourcefile, which instantiates the 
//  lex_functor. While the cpp_re2c_token.hpp file may be included everywhere,
//  this file (cpp_re2c_lexer.hpp) should be included only once. This allows
//  to decouple the lexer interface from the lexer implementation and reduces 
//  compilation time.
//
///////////////////////////////////////////////////////////////////////////////

template <typename IteratorT, typename PositionT>
RE2C_NEW_LEXER_INLINE
lex_input_interface<lex_token<IteratorT, PositionT> > *
new_lexer_gen<IteratorT, PositionT>::new_lexer(IteratorT const &first,
    IteratorT const &last, std::string const &fname)
{
    return new lex_functor<IteratorT, PositionT>(first, last, fname);
}

#undef RE2C_NEW_LEXER_INLINE

///////////////////////////////////////////////////////////////////////////////
}   // namespace re2clex
}   // namespace cpplexer
     
#endif // !defined(_CPP_RE2C_LEXER_HPP__B81A2629_D5B1_4944_A97D_60254182B9A8__INCLUDED_)
