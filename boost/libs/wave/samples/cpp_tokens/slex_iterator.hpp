/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library

    Definition of the lexer iterator 
    
    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost 
    Software License, Version 1.0. (See accompanying file 
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(SLEX_ITERATOR_HPP_AF0C37E3_CBD8_4F33_A225_51CF576FA61F_INCLUDED)
#define SLEX_ITERATOR_HPP_AF0C37E3_CBD8_4F33_A225_51CF576FA61F_INCLUDED

#include <string>
#include <iostream>

#include <boost/assert.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/spirit/iterator/multi_pass.hpp>

#include <boost/wave/language_support.hpp>
#include <boost/wave/util/file_position.hpp>
#include <boost/wave/util/functor_input.hpp>

#include "slex_interface.hpp"

///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave {
namespace cpplexer {
namespace slex {
namespace impl {

///////////////////////////////////////////////////////////////////////////////
//  
//  lex_iterator_functor_shim
//
///////////////////////////////////////////////////////////////////////////////

template <typename TokenT> 
class slex_iterator_functor_shim 
{
public:
    template <typename IteratorT>
    slex_iterator_functor_shim(IteratorT const &first, IteratorT const &last, 
            typename TokenT::position_type const &pos, 
            boost::wave::language_support language)
    :   functor_ptr(slex_input_interface<TokenT>
            ::new_lexer(first, last, pos, language)) 
    {}

// interface to the boost::spirit::multi_pass_policies::functor_input policy
    typedef TokenT result_type;

    /*static*/ result_type const eof;
    
    result_type operator()() 
    { 
        BOOST_ASSERT(0 != functor_ptr.get());
        return functor_ptr->get(); 
    }
    void set_position(typename TokenT::position_type const &pos)
    {
        BOOST_ASSERT(0 != functor_ptr.get());
        functor_ptr->set_position(pos);
    }
    
private:
    boost::shared_ptr<slex_input_interface<TokenT> > functor_ptr;
};

///////////////////////////////////////////////////////////////////////////////
//  eof token
//template <typename TokenT>
//typename slex_iterator_functor_shim<TokenT>::result_type const
//    slex_iterator_functor_shim<TokenT>::eof = 
//        typename slex_iterator_functor_shim<TokenT>::result_type();

///////////////////////////////////////////////////////////////////////////////
}   // namespace impl

///////////////////////////////////////////////////////////////////////////////
//  
//  slex_iterator
//
//      A generic C++ lexer interface class, which allows to plug in different
//      lexer implementations (template parameter LexT). The following 
//      requirement apply:
//
//          - the lexer type should have a function implemented, which returnes
//            the next lexed token from the input stream:
//                typename LexT::token_type get();
//          - at the end of the input stream this function should return the
//            eof token equivalent
//          - the lexer should implement a constructor taking two iterators
//            pointing to the beginning and the end of the input stream and
//            a third parameter containing the name of the parsed input file,
//            the 4th parameter contains the information about the mode the 
//            preprocessor is used in (C99/C++ mode etc.)
//
///////////////////////////////////////////////////////////////////////////////

template <typename TokenT>
class slex_iterator 
:   public boost::spirit::multi_pass<
        impl::slex_iterator_functor_shim<TokenT>,
        boost::wave::util::functor_input
    >
{
    typedef impl::slex_iterator_functor_shim<TokenT> input_policy_type;
    typedef 
        boost::spirit::multi_pass<input_policy_type, 
                boost::wave::util::functor_input>
        base_t;
    typedef slex_iterator<TokenT>                    self_type;
    
public:
    typedef TokenT token_type;
    
    slex_iterator()
    {}
    
    template <typename IteratorT>
    slex_iterator(IteratorT const &first, IteratorT const &last, 
            typename TokenT::position_type const &pos, 
            boost::wave::language_support language)
    :   base_t(input_policy_type(first, last, pos, language))
    {}
};

///////////////////////////////////////////////////////////////////////////////
}   // slex
}   // namespace cpplexer
}   // namespace wave
}   // namespace boost

#endif // !defined(SLEX_ITERATOR_HPP_AF0C37E3_CBD8_4F33_A225_51CF576FA61F_INCLUDED)
