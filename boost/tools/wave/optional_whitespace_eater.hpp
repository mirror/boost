/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(OPTIONAL_WHITESPACE_EATER_HPP_INCLUDED)
#define OPTIONAL_WHITESPACE_EATER_HPP_INCLUDED

#include <boost/wave/whitespace_handling.hpp>

///////////////////////////////////////////////////////////////////////////////
//  
//  The optional_whitespace_eater policy is used to handle the different 
//  options of whitespace skipping supported by the wave driver executable. It 
//  is based on the eat_whitespace component provided by the wave library but 
//  optionally overwrites the whitespace skipping at all to allow the generated
//  whitespace to appear in the generated output.
//
//  This policy type is used as a template parameter to the 
//  boost::wave::context<> object.
//
///////////////////////////////////////////////////////////////////////////////
template <typename TokenT>
class optional_whitespace_eater
:   public boost::wave::context_policies::eat_whitespace<TokenT>
{
    typedef boost::wave::context_policies::eat_whitespace<TokenT> base_type;
    
public:
    optional_whitespace_eater(bool preserve_whitespace, bool preserve_comments)
    :   base_type(preserve_comments), 
        preserve_whitespace(preserve_whitespace)
    {}

    bool may_skip (TokenT &token, bool &skipped_newline)
    {
        // if whitespace should be preserved return false always
        return !preserve_whitespace ? 
            this->base_type::may_skip(token, skipped_newline) :
            false;
    }
    
private:
    bool preserve_whitespace;
};

#endif // !defined(OPTIONAL_WHITESPACE_EATER_HPP_INCLUDED)
