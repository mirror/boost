#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct.hpp
    /// For constructing an arbitrary type from a bunch of transforms. This assumes
    /// that all the grammars corresponding to the transforms are equivalent; that is,
    /// that they match the same expressions.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_CONSTRUCT_HPP_EAN_12_26_2006
    #define BOOST_PROTO_TRANSFORM_CONSTRUCT_HPP_EAN_12_26_2006

    #include <boost/xpressive/proto/detail/prefix.hpp>

    #include <boost/preprocessor/iterate.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>

    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto { namespace transform
    {
        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/construct.hpp>))
        #include BOOST_PP_ITERATE()
        #undef BOOST_PP_ITERATION_PARAMS_1
    }}}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Type BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)>
        struct construct<
            Type
            BOOST_PP_ENUM_TRAILING_PARAMS(N, Grammar)
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT)
          , void
        >
          : Grammar0
        {
            template<typename, typename, typename>
            struct apply
            {
                typedef Type type;
            };

            template<typename Expr, typename State, typename Visitor>
            static Type call(Expr const &expr, State const &state, Visitor &visitor)
            {
                return Type(
                    BOOST_PP_ENUM_BINARY_PARAMS(N, Grammar, ::call(expr, state, visitor) BOOST_PP_INTERCEPT)
                );
            }
        };

    #undef N

#endif
