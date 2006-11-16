/*=============================================================================
    Copyright (c) 2002-2006 Joel de Guzman
    http://spirit.sourceforge.net/

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_QUICKBOOK_PREPROCESSOR_HPP)
#define BOOST_SPIRIT_QUICKBOOK_PREPROCESSOR_HPP

//~ #include "detail/utils.hpp"
#include <boost/spirit/core.hpp>
//~ #include <boost/spirit/utility/confix.hpp>
//~ #include <boost/spirit/utility/chset.hpp>
//~ #include <boost/spirit/actor/assign_actor.hpp>
//~ #include <boost/spirit/dynamic/if.hpp>

namespace quickbook
{
    using namespace boost::spirit;

    template <typename Rule, typename Action>
    inline void
    simple_markup(Rule& simple, char mark, Action const& action, Rule const& eol)
    {
        simple =
            mark >>
            (
                (
                    graph_p                     // A single char. e.g. *c*
                    >> eps_p(mark
                        >> (space_p | punct_p | end_p)) 
                                                // space_p, punct_p or end_p 
                )                               // must follow mark
            |   
                (   graph_p >>                  // graph_p must follow mark
                    *(anychar_p -
                        (   (eol >> eol)        // Make sure that we don't go
                        |   (graph_p >> mark)   // past a single block
                        )
                    ) 
                    >> (graph_p - '\\')         // graph_p (but not the back-slash)
                                                // must precede mark
                    >> eps_p(mark
                        >> (space_p | punct_p | end_p)) 
                                                // space_p, punct_p or end_p 
                )                               // must follow mark
            )                                   [action]
            >> mark
            ;
    }

    template <typename Actions>
    struct preprocessor : grammar<preprocessor<Actions> >
    {
        preprocessor(Actions& actions)
            : actions(actions) {}

        template <typename Scanner>
        struct definition
        {
            definition(preprocessor const& self)
            {
                Actions& actions = self.actions;



                start_ = +anychar_p[actions.];
            }
            
            rule<Scanner> start_;

            rule<Scanner> const&
            start() const { return start_; }
        };

        Actions& actions;
    };
}

#endif // BOOST_SPIRIT_QUICKBOOK_PREPROCESSOR_HPP

