///////////////////////////////////////////////////////////////////////////////
/// \file matches.hpp
/// Contains definition of matches\<\> metafunction for determining if
/// a given expression matches a given pattern.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006
#define BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006

#include <boost/config.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/placeholders.hpp>

namespace boost { namespace proto
{

    namespace detail
    {
        typedef char match_t;
        typedef char (&no_match_t)[2];

        template<typename Expr>
        struct expr_check;

        template<typename Expr, typename Grammar>
        struct terminal_matches
          : mpl::false_
        {};

        template<typename Grammar>
        struct terminal_matches<Grammar, Grammar>
          : mpl::true_
        {};

        template<typename Expr>
        struct terminal_matches<Expr, mpl::_>
          : mpl::true_
        {};

        template<typename Args>
        struct expr_check< basic_expr<terminal_tag, Args, 1> >
        {
            template<typename Tag1, typename Args1, long N1>
            static
            no_match_t
            match( basic_expr<Tag1, Args1, N1> const & );

            typedef typename meta::arg<
                basic_expr<terminal_tag, Args, 1>
            >::type arg_type;

            template<typename Args1>
            static
                typename mpl::if_<
                    terminal_matches< typename meta::arg< basic_expr<terminal_tag, Args1, 1> >::type, arg_type >
                  , match_t
                  , no_match_t
                >::type
            match( basic_expr<terminal_tag, Args1, 1> const & );
        };

        template<typename Tag, typename Args>
        struct expr_check< basic_expr<Tag, Args, 1> >
        {
            template<typename Tag1, typename Args1, long N1>
            static
            no_match_t
            match( basic_expr<Tag1, Args1, N1> const & );

            typedef typename meta::arg<
                basic_expr<Tag, Args, 1>
            >::type arg_type;

            template<typename Args1>
            static
                typename mpl::if_c<(
                        matches< typename meta::arg< basic_expr<Tag, Args1, 1> >::type, arg_type >::value
                    )
                  , match_t
                  , no_match_t
                >::type
            match( basic_expr<Tag, Args1, 1> const & );
        };

        template<typename Tag, typename Args>
        struct expr_check< basic_expr<Tag, Args, 2> >
        {
            template<typename Tag1, typename Args1, long N1>
            static
            no_match_t
            match( basic_expr<Tag1, Args1, N1> const & );

            typedef typename meta::left<
                basic_expr<Tag, Args, 2>
            >::type left_type;

            typedef typename meta::right<
                basic_expr<Tag, Args, 2>
            >::type right_type;

            template<typename Args1>
            static
                typename mpl::if_c<(
                        matches< typename meta::left< basic_expr<Tag, Args1, 2> >::type, left_type >::value
                     && matches< typename meta::right< basic_expr<Tag, Args1, 2> >::type, right_type >::value
                    )
                  , match_t
                  , no_match_t
                >::type
            match( basic_expr<Tag, Args1, 2> const & );
        };

    #define BOOST_PROTO_MATCHES_N_FUN(z, n, data)\
        matches<\
            typename meta::arg_c< basic_expr<Tag, Args1, data>, n >::type\
          , typename meta::arg_c< basic_expr<Tag, Args, data>, n >::type\
        >::value &&\
        /**/

    #define BOOST_PROTO_EXPR_CHECK_FUN(z, n, data)\
        template<typename Tag, typename Args>\
        struct expr_check< basic_expr<Tag, Args, n> >\
        {\
            template<typename Tag1, typename Args1, long N1>\
            static\
            no_match_t\
            match( basic_expr<Tag1, Args1, N1> const & );\
            \
            template<typename Args1>\
            static\
                typename mpl::if_c<(\
                        BOOST_PP_REPEAT_ ## z(n, BOOST_PROTO_MATCHES_N_FUN, n) true\
                    )\
                  , match_t\
                  , no_match_t\
                >::type\
            match( basic_expr<Tag, Args1, n> const & );\
        };\
        /**/

        BOOST_PP_REPEAT_FROM_TO(
            3, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_EXPR_CHECK_FUN, ~)

    #undef BOOST_PROTO_EXPR_CHECK_FUN
    #undef BOOST_PROTO_MATCHES_N_FUN

        template<>
        struct expr_check< mpl::_ >
        {
            template<typename Expr>
            static
            match_t
            match( Expr const & );
        };

        // by default, assume parameter is an expression generator ... 
        template<typename Expr>
        struct deref
        {
            typedef typename Expr::type type;
        };

        // ... but it could be a plain expression ...
        template<typename Tag, typename Args, long Arity>
        struct deref<basic_expr<Tag, Args, Arity> >
        {
            typedef basic_expr<Tag, Args, Arity> type;
        };

        // ... or the placeholder
        template<>
        struct deref<mpl::_>
        {
            typedef mpl::_ type;
        };
    }

    template<typename Expr, typename Grammar>
    struct matches
    {
    private:
        static Expr const &expr;
    public:
        BOOST_STATIC_CONSTANT(bool, value = sizeof(detail::expr_check<typename detail::deref<Grammar>::type>::match(expr)) == sizeof(detail::match_t));
        typedef mpl::bool_<value> type;
    };

}}

#endif

