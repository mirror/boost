//  Hannibal: partial C++ grammar to parse C++ type information
//  Copyright (c) 2005 Danny Havenith
// 
//  Boost.Wave: A Standard compliant C++ preprocessor
//  Copyright (c) 2001-2006 Hartmut Kaiser
// 
//  http://www.boost.org/
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define HANNIBAL_DUMP_PARSE_TREE 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/spirit/tree/ast.hpp>
#include <boost/spirit/tree/tree_to_xml.hpp>

///////////////////////////////////////////////////////////////////////////////
//  Include Wave itself
#include <boost/wave.hpp>

///////////////////////////////////////////////////////////////////////////////
// Include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

///////////////////////////////////////////////////////////////////////////////
//  Include the Hannibal grammar
#include "translation_unit_parser.h"
#include "translation_unit_skipper.h"

///////////////////////////////////////////////////////////////////////////////
namespace {

    typedef boost::wave::cpplexer::lex_token<> token_type;
    
    inline int 
    get_token_id(token_type const &t) 
    { 
        return boost::wave::token_id(t); 
    }
    
    inline token_type::string_type
    get_token_value(token_type const &t) 
    { 
        return t.get_value(); 
    }

}

///////////////////////////////////////////////////////////////////////////////
// main entry point
int main(int argc, char *argv[])
{
    if (2 != argc) {
        std::cerr << "Usage: hannibal infile" << std::endl;
        return -1;
    }
    
// current file position is saved for exception handling
boost::wave::util::file_position_type current_position;

    try {
    //  Open and read in the specified input file.
    std::ifstream instream(argv[1]);
    std::string instring;

        if (!instream.is_open()) {
            std::cerr << "Hannibal: could not open input file: " << argv[1] 
                      << std::endl;
            return -2;
        }
        instream.unsetf(std::ios::skipws);
        instring = std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                                std::istreambuf_iterator<char>());
            
    //  The template boost::wave::cpplexer::lex_token<> is the token type to be 
    //  used by the Wave library.
        typedef boost::wave::cpplexer::lex_token<> token_type;
    
    //  The template boost::wave::cpplexer::lex_iterator<> is the lexer type to
    //  be used by the Wave library.
        typedef boost::wave::cpplexer::lex_iterator<token_type> lex_iterator_type;
        
    //  This is the resulting context type to use. The first template parameter
    //  should match the iterator type to be used during construction of the
    //  corresponding context object (see below).
        typedef boost::wave::context<std::string::iterator, lex_iterator_type>
            context_type;

    // The preprocessor iterator shouldn't be constructed directly. It is 
    // to be generated through a wave::context<> object. This wave:context<> 
    // object is to be used additionally to initialize and define different 
    // parameters of the actual preprocessing (not done here).
    //
    // The preprocessing of the input stream is done on the fly behind the 
    // scenes during iteration over the context_type::iterator_type stream.
    context_type ctx (instring.begin(), instring.end(), argv[1]);

    // analyze the input file
    context_type::iterator_type first = ctx.begin();
    context_type::iterator_type last = ctx.end();
        
        typedef boost::spirit::tree_parse_info<context_type::iterator_type> 
            result_type;

#if HANNIBAL_DUMP_PARSE_TREE != 0
    translation_unit_grammar::rule_map_type rule_map;
    translation_unit_grammar g(&rule_map);
#else
    translation_unit_grammar g;
#endif
    translation_unit_skipper s; 

    // parse the input file
    result_type pi = boost::spirit::ast_parse(first, last, g, s);
        
        if (pi.full) {
            std::cout << "Hannibal: parsed sucessfully: " << argv[1] 
                      << std::endl;
                      
#if HANNIBAL_DUMP_PARSE_TREE != 0
            // generate xml dump from parse tree, if requested
            boost::spirit::tree_to_xml(std::cerr, pi.trees, "", rule_map, 
                &get_token_id, &get_token_value);
#endif
        }
    }
    catch (boost::wave::cpp_exception &e) {
    // some preprocessing error
        std::cerr 
            << e.file_name() << ":" << e.line_no() << ":" << e.column_no() << ": "
            << e.description() << std::endl;
        return 2;
    }
    catch (boost::wave::cpplexer::lexing_exception const &e) {
    // some lexing error
        std::cerr 
            << e.file_name() << ":" << e.line_no() << ":" << e.column_no() << ": "
            << e.description() << std::endl;
        return 2;
    }
    catch (std::exception &e) {
    // use last recognized token to retrieve the error position
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "exception caught: " << e.what()
            << std::endl;
        return 3;
    }
    catch (...) {
    // use last recognized token to retrieve the error position
        std::cerr 
            << current_position.get_file() 
            << "(" << current_position.get_line() << "): "
            << "unexpected exception caught." << std::endl;
        return 4;
    }
    return 0;
}
