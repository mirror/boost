/*=============================================================================
    Wave: A Standard compliant C++ preprocessor library

    http://spirit.sourceforge.net/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost
    Software License, Version 1.0. (See accompanying file
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#if !defined(CPP_CHLIT_GRAMMAR_HPP_9527D349_6592_449A_A409_42A001E6C64C_INCLUDED)
#define CPP_CHLIT_GRAMMAR_HPP_9527D349_6592_449A_A409_42A001E6C64C_INCLUDED

#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute/closure.hpp>

#include <boost/spirit/phoenix/operators.hpp>
#include <boost/spirit/phoenix/primitives.hpp>
#include <boost/spirit/phoenix/statements.hpp>
#include <boost/spirit/phoenix/functions.hpp>

#include <boost/wave/wave_config.hpp>   
#include <boost/wave/cpp_exceptions.hpp>   
#include <boost/wave/grammars/cpp_literal_grammar_gen.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Reusable grammar to parse a C++ style character literal 
//
///////////////////////////////////////////////////////////////////////////////
namespace boost {
namespace wave { 
namespace grammars {

namespace closures {

    struct chlit_closure 
    :   boost::spirit::closure<chlit_closure, unsigned int> 
    {
        member1 value;
    };
}

namespace impl {

///////////////////////////////////////////////////////////////////////////////
//
//  compose a multibyte character literal
//
///////////////////////////////////////////////////////////////////////////////
    struct compose_character_literal {

        template <typename ResultT, typename ArgT>
        struct result { 
        
            typedef unsigned int type; 
        };

        unsigned int 
        operator()(unsigned int res, unsigned int character) const
        { 
            unsigned int retval = (res << 8) | (character & 0xff);
            return retval;
        }
    };
    phoenix::function<compose_character_literal> const compose;

}   // namespace impl

///////////////////////////////////////////////////////////////////////////////
//  define, whether the rule's should generate some debug output
#define TRACE_CHLIT_GRAMMAR \
    bool(BOOST_SPIRIT_DEBUG_FLAGS_CPP & BOOST_SPIRIT_DEBUG_FLAGS_CHLIT_GRAMMAR) \
    /**/

struct chlit_grammar :
    public boost::spirit::grammar<chlit_grammar, 
        closures::chlit_closure::context_t>
{
    chlit_grammar()
    {
        BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(*this, "chlit_grammar", 
            TRACE_CHLIT_GRAMMAR);
    }
    
    template <typename ScannerT>
    struct definition
    {
        typedef 
            boost::spirit::rule<ScannerT, closures::chlit_closure::context_t> 
            rule_t;

        rule_t ch_lit;

        definition(chlit_grammar const &self)
        {
            using namespace boost::spirit;
            using namespace phoenix;
            
            ch_lit
                =  !ch_p('L') 
                    >>  ch_p('\'')[self.value = val(0)]
                    >> +(   (
                            ch_p('\\') 
                            >>  (   ch_p('a')    // BEL
                                    [
                                        self.value = impl::compose(self.value, val(0x07))
                                    ]
                                |   ch_p('b')    // BS
                                    [
                                        self.value = impl::compose(self.value, val(0x08))
                                    ]
                                |   ch_p('t')    // HT
                                    [
                                        self.value = impl::compose(self.value, val(0x09))
                                    ]
                                |   ch_p('n')    // NL
                                    [
                                        self.value = impl::compose(self.value, val(0x0a))
                                    ]
                                |   ch_p('v')    // VT
                                    [
                                        self.value = impl::compose(self.value, val(0x0b))
                                    ]
                                |   ch_p('f')    // FF
                                    [
                                        self.value = impl::compose(self.value, val(0x0c))
                                    ]
                                |   ch_p('r')    // CR
                                    [
                                        self.value = impl::compose(self.value, val(0x0d))
                                    ]
                                |   ch_p('?')
                                    [
                                        self.value = impl::compose(self.value, val('?'))
                                    ]
                                |   ch_p('\'')
                                    [
                                        self.value = impl::compose(self.value, val('\''))
                                    ]
                                |   ch_p('\"')
                                    [
                                        self.value = impl::compose(self.value, val('\"'))
                                    ]
                                |   ch_p('\\')
                                    [
                                        self.value = impl::compose(self.value, val('\\'))
                                    ]
                                |   ch_p('x') 
                                    >>  uint_parser<unsigned int, 16, 2, 2>()
                                    [
                                        self.value = impl::compose(self.value, arg1)
                                    ]
                                |   ch_p('u') 
                                    >>  uint_parser<unsigned int, 16, 4, 4>()
                                        [
                                            self.value = impl::compose(self.value, arg1)
                                        ]
                                |   ch_p('U')
                                    >>  uint_parser<unsigned int, 16, 8, 8>()
                                        [
                                            self.value = impl::compose(self.value, arg1)
                                        ]
                                |   uint_parser<unsigned int, 8, 1, 3>()
                                    [
                                        self.value = impl::compose(self.value, arg1)
                                    ]
                                )
                            )
                        |   ~eps_p(ch_p('\'')) >> anychar_p
                            [
                                self.value = impl::compose(self.value, arg1)
                            ]
                        )
                    >>  ch_p('\'')
                ;

            BOOST_SPIRIT_DEBUG_TRACE_RULE(ch_lit, TRACE_CHLIT_GRAMMAR);
        }

    // start rule of this grammar
        rule_t const& start() const
        { return ch_lit; }
    };
};

#undef TRACE_CHLIT_GRAMMAR

///////////////////////////////////////////////////////////////////////////////
//  
//  The following function is defined here, to allow the separation of 
//  the compilation of the intlit_grammap from the function using it.
//  
///////////////////////////////////////////////////////////////////////////////

#if BOOST_WAVE_SEPARATE_GRAMMAR_INSTANTIATION != 0
#define BOOST_WAVE_CHLITGRAMMAR_GEN_INLINE
#else
#define BOOST_WAVE_CHLITGRAMMAR_GEN_INLINE inline
#endif 

template <typename TokenT>
BOOST_WAVE_CHLITGRAMMAR_GEN_INLINE 
unsigned int
chlit_grammar_gen<TokenT>::evaluate(TokenT const &token)
{
    using namespace boost::spirit;
    
static chlit_grammar g;
unsigned int result = 0;
typename TokenT::string_type const &token_val = token.get_value();
parse_info<typename TokenT::string_type::const_iterator> hit =
    parse(token_val.begin(), token_val.end(), g[spirit_assign_actor(result)]);

    if (!hit.hit) {
        BOOST_WAVE_THROW(preprocess_exception, ill_formed_expression, 
            token_val, token.get_position());
    }
    return result;
}

#undef BOOST_WAVE_CHLITGRAMMAR_GEN_INLINE

///////////////////////////////////////////////////////////////////////////////
}   // namespace grammars
}   // namespace wave
}   // namespace boost

#endif // !defined(CPP_CHLIT_GRAMMAR_HPP_9527D349_6592_449A_A409_42A001E6C64C_INCLUDED)
