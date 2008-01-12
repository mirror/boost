#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file bind.hpp
    /// Contains definition of the bind<> transform.
    //
    //  Copyright 2007 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_BIND_HPP_EAN_12_02_2007
    #define BOOST_PROTO_TRANSFORM_BIND_HPP_EAN_12_02_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/transform/make.hpp>
    #include <boost/xpressive/proto/transform/call.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace transform
        {
            template<typename Fun>
            struct bind : callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                  : call<
                        typename make<Fun>::template result<void(Expr, State, Visitor)>::type
                    >::template result<void(Expr, State, Visitor)>
                {};

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    return call<
                        typename make<Fun>::template result<void(Expr, State, Visitor)>::type
                    >()(expr, state, visitor);
                }
            };

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/bind.hpp>))
        #include BOOST_PP_ITERATE()

        }

        template<typename Fun>
        struct is_callable<transform::bind<Fun> >
          : mpl::true_
        {};

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            template<typename Return BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
            struct bind<Return(BOOST_PP_ENUM_PARAMS(N, A))> : callable
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                  : call<
                        typename make<Return>::template result<void(Expr, State, Visitor)>::type(BOOST_PP_ENUM_PARAMS(N, A))
                    >::template result<void(Expr, State, Visitor)>
                {};

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    return call<
                        typename make<Return>::template result<void(Expr, State, Visitor)>::type(BOOST_PP_ENUM_PARAMS(N, A))
                    >()(expr, state, visitor);
                }
            };

    #undef N

#endif
