#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file args.hpp
    /// Contains definition of args\<\> class template.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_ARGS_HPP_EAN_04_01_2005
    #define BOOST_PROTO_ARGS_HPP_EAN_04_01_2005

    #include <boost/xpressive/proto/detail/prefix.hpp>

    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/repeat_from_to.hpp>
    #include <boost/mpl/void.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>

    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {
    #define BOOST_PROTO_DEFINE_ARG_N(z, n, data)\
        typedef BOOST_PP_CAT(Arg, n) BOOST_PP_CAT(arg, n);

    #define BOOST_PROTO_DEFINE_VOID_N(z, n, data)\
        typedef mpl::void_ BOOST_PP_CAT(arg, n);

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/args.hpp>))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_1

    #undef BOOST_PROTO_DEFINE_ARG_N
    #undef BOOST_PROTO_DEFINE_VOID_N

    }}
    #endif

#else

    #define N BOOST_PP_ITERATION()

        template< BOOST_PP_ENUM_PARAMS(N, typename Arg) >
        struct BOOST_PP_CAT(args, N)
        {
            BOOST_STATIC_CONSTANT(long, size = N);
            BOOST_PP_REPEAT(N, BOOST_PROTO_DEFINE_ARG_N, ~)
            BOOST_PP_REPEAT_FROM_TO(N, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_VOID_N, ~)
            typedef BOOST_PP_CAT(Arg, BOOST_PP_DEC(N)) back_;
        };

    #undef N

#endif
