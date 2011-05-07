#ifndef BOOST_PP_IS_ITERATING

    ///////////////////////////////////////////////////////////////////////////////
    /// \file template_arity.hpp
    /// Replace all nodes stored by reference by nodes stored by value.
    //
    //  Copyright 2011 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    //
    //  This file is based on a similar one in MPL from Aleksey Gurtovoy.

    #ifndef BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07
    #define BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07

    // Somewhat indirect definition of BOOST_PROTO_TEMPLATE_ARITY_PARAM is
    // to overcome a shortcoming of the Wave tool used to generate the
    // pre-preprocessed headers.
    #define BOOST_PROTO_TEMPLATE_ARITY_PARAM BOOST_PROTO_TEMPLATE_ARITY_PARAM2
    #define BOOST_PROTO_TEMPLATE_ARITY_PARAM2(param)

    #ifdef BOOST_PROTO_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

        #include <boost/preprocessor/cat.hpp>
        #include <boost/preprocessor/inc.hpp>
        #include <boost/preprocessor/iteration/iterate.hpp>
        #include <boost/preprocessor/repetition/enum_params.hpp>
        #include <boost/mpl/int.hpp>
        #include <boost/proto/proto_fwd.hpp>

        #undef BOOST_PROTO_TEMPLATE_ARITY_PARAM2
        #define BOOST_PROTO_TEMPLATE_ARITY_PARAM2(param) , param

        namespace boost { namespace proto { namespace detail
        {
            sized_type<1>::type arity_helper(...);

            #define BOOST_PP_ITERATION_PARAMS_1                                                             \
                (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/template_arity.hpp>))
            #include BOOST_PP_ITERATE()

            template<typename F, int N, int Size>
            struct template_arity_impl2
              : mpl::int_<Size - 1>
            {};

            template<typename F, int N = BOOST_PROTO_MAX_ARITY>
            struct template_arity
              : template_arity_impl2<
                    F
                  , N
                  , sizeof(detail::arity_helper((F **)0, (mpl::int_<N> *)0))
                >
            {};

            template<typename F, int N>
            struct template_arity_impl2<F, N, 1>
              : template_arity<F, N-1>
            {};

            template<typename F>
            struct template_arity_impl2<F, 0, 1>
              : mpl::int_<-1>
            {};

        }}}

    #endif // BOOST_PROTO_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
    #endif // BOOST_PROTO_DETAIL_TEMPLATE_ARITY_HPP_EAN_2011_05_07

#else

    #define N BOOST_PP_ITERATION()

        template<
            template<BOOST_PP_ENUM_PARAMS(N, typename P)> class F
          , BOOST_PP_ENUM_PARAMS(N, typename T)
        >
        sized_type<BOOST_PP_INC(N)>::type arity_helper(F<BOOST_PP_ENUM_PARAMS(N, T)> **, mpl::int_<N> *);

    #undef N

#endif // BOOST_PP_IS_ITERATING
