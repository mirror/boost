#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file when.hpp
    /// Definition of when transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_WHEN_HPP_EAN_10_29_2007
    #define BOOST_PROTO_TRANSFORM_WHEN_HPP_EAN_10_29_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/transform/call.hpp>
    #include <boost/xpressive/proto/transform/make.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto { namespace transform
    {
        // Simple transform, takes a raw transform and
        // applies it directly.
        template<typename Grammar, typename Fun>
        struct when
          : Fun
        {
            typedef typename Grammar::proto_base_expr proto_base_expr;
        };

        template<typename Grammar, typename Fun>
        struct when<Grammar, Fun *>
          : when<Grammar, Fun>
        {};

        template<typename Fun>
        struct otherwise
          : when<_, Fun>
        {};

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/when.hpp>))
        #include BOOST_PP_ITERATE()

    }}} // namespace boost::proto::transform

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Grammar, typename Return BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct when<Grammar, Return(BOOST_PP_ENUM_PARAMS(N, A))>
          : proto::callable
        {
            typedef typename Grammar::proto_base_expr proto_base_expr;

            template<typename Sig>
            struct result;

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef
                    typename mpl::if_<
                        is_callable<Return>
                      , call<Return(BOOST_PP_ENUM_PARAMS(N, A))> // "Return" is a function to call
                      , make<Return(BOOST_PP_ENUM_PARAMS(N, A))> // "Return" is an object to construct
                    >::type
                impl;

                typedef typename impl::template result<void(Expr, State, Visitor)>::type type;
            };

            /// Function call operator
            ///
            template<typename Expr, typename State, typename Visitor>
            typename result<void(Expr, State, Visitor)>::type
            operator ()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                return typename mpl::if_<
                    is_callable<Return>
                  , call<Return(BOOST_PP_ENUM_PARAMS(N, A))>
                  , make<Return(BOOST_PP_ENUM_PARAMS(N, A))>
                >::type()(expr, state, visitor);
            }
        };

    #undef N

#endif
