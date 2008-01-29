#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file call.hpp
    /// Contains definition of the call<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_CALL_HPP_EAN_11_02_2007
    #define BOOST_PROTO_TRANSFORM_CALL_HPP_EAN_11_02_2007

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/detail/dont_care.hpp>
    #include <boost/xpressive/proto/detail/as_lvalue.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace transform
        {
            namespace detail
            {
                using proto::detail::uncv;
                using proto::detail::as_lvalue;
                using proto::detail::dont_care;
                typedef char (&yes_type)[2];
                typedef char no_type;

                struct private_type_
                {
                    private_type_ const &operator ,(int) const;
                };

                template<typename T>
                yes_type check_fun_arity(T const &);

                no_type check_fun_arity(private_type_ const &);

                template<typename Fun>
                struct callable0_wrap : Fun
                {
                    callable0_wrap();
                    typedef private_type_ const &(*pfun0)();
                    operator pfun0() const;
                };

                template<typename Fun>
                struct callable1_wrap : Fun
                {
                    callable1_wrap();
                    typedef private_type_ const &(*pfun1)(dont_care);
                    operator pfun1() const;
                };

                template<typename Fun>
                struct callable2_wrap : Fun
                {
                    callable2_wrap();
                    typedef private_type_ const &(*pfun2)(dont_care, dont_care);
                    operator pfun2() const;
                };

                template<typename Fun>
                struct arity0
                {
                    static callable0_wrap<Fun> &fun;

                    static int const value =
                        sizeof(yes_type) == sizeof(check_fun_arity((fun(), 0)))
                      ? 0
                      : 3;
                };

                template<typename Fun, typename A0>
                struct arity1
                {
                    static callable1_wrap<Fun> &fun;
                    static A0 &a0;

                    static int const value =
                        sizeof(yes_type) == sizeof(check_fun_arity((fun(a0), 0)))
                      ? 1
                      : 3;
                };

                template<typename Fun, typename A0, typename A1>
                struct arity2
                {
                    static callable2_wrap<Fun> &fun;
                    static A0 &a0;
                    static A1 &a1;

                    static int const value =
                        sizeof(yes_type) == sizeof(check_fun_arity((fun(a0, a1), 0)))
                      ? 2
                      : 3;
                };

                template<typename Fun, typename Expr, typename State, typename Visitor>
                struct call3
                {
                    typedef typename boost::result_of<Fun(Expr, State, Visitor)>::type type;

                    template<typename Expr2, typename State2, typename Visitor2>
                    static type call(Expr2 &expr, State2 &state, Visitor2 &visitor)
                    {
                        Fun f;
                        return f(expr, state, visitor);
                    }
                };

                template<typename Fun, typename Expr, typename State, typename Visitor
                  , int Arity = arity0<Fun>::value>
                struct call0
                  : call3<Fun, Expr, State, Visitor>
                {};

                template<typename Fun, typename Expr, typename State, typename Visitor>
                struct call0<Fun, Expr, State, Visitor, 0>
                {
                    typedef typename boost::result_of<Fun()>::type type;

                    template<typename Expr2, typename State2, typename Visitor2>
                    static type call(Expr2 &, State2 &, Visitor2 &)
                    {
                        Fun f;
                        return f();
                    }
                };

                template<typename Fun, typename Expr, typename State, typename Visitor
                  , int Arity = arity1<Fun, Expr>::value>
                struct call1
                  : call3<Fun, Expr, State, Visitor>
                {};

                template<typename Fun, typename Expr, typename State, typename Visitor>
                struct call1<Fun, Expr, State, Visitor, 1>
                {
                    typedef typename boost::result_of<Fun(Expr)>::type type;

                    template<typename Expr2, typename State2, typename Visitor2>
                    static type call(Expr2 &expr, State2 &, Visitor2 &)
                    {
                        Fun f;
                        return f(expr);
                    }
                };

                template<typename Fun, typename Expr, typename State, typename Visitor
                  , int Arity = arity2<Fun, Expr, State>::value>
                struct call2
                  : call3<Fun, Expr, State, Visitor>
                {};

                template<typename Fun, typename Expr, typename State, typename Visitor>
                struct call2<Fun, Expr, State, Visitor, 2>
                {
                    typedef typename boost::result_of<Fun(Expr, State)>::type type;

                    template<typename Expr2, typename State2, typename Visitor2>
                    static type call(Expr2 &expr, State2 &state, Visitor2 &)
                    {
                        Fun f;
                        return f(expr, state);
                    }
                };
            }

            template<typename Fun>
            struct call : Fun
            {
                BOOST_PROTO_CALLABLE()
            };

            template<typename Fun>
            struct call<Fun()> : proto::callable
            {
                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef
                        typename detail::call0<
                            Fun
                          , Expr
                          , State
                          , Visitor
                        >::type
                    type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef
                        detail::call0<
                            Fun
                          , Expr
                          , State
                          , Visitor
                        >
                    impl;

                    return impl::call(expr, state, visitor);
                }
            };

            template<typename Fun, typename Arg0>
            struct call<Fun(Arg0)> : proto::callable
            {
                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef
                        typename detail::call1<
                            Fun
                          , typename when<_, Arg0>::template result<void(Expr, State, Visitor)>::type
                          , State
                          , Visitor
                        >::type
                    type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef
                        detail::call1<
                            Fun
                          , typename when<_, Arg0>::template result<void(Expr, State, Visitor)>::type
                          , State
                          , Visitor
                        >
                    impl;

                    return impl::call(
                        detail::as_lvalue(when<_, Arg0>()(expr, state, visitor))
                      , state
                      , visitor
                    );
                }
            };

            template<typename Fun, typename Arg0, typename Arg1>
            struct call<Fun(Arg0, Arg1)> : proto::callable
            {
                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef
                        typename detail::call2<
                            Fun
                          , typename when<_, Arg0>::template result<void(Expr, State, Visitor)>::type
                          , typename when<_, Arg1>::template result<void(Expr, State, Visitor)>::type
                          , Visitor
                        >::type
                    type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef
                        detail::call2<
                            Fun
                          , typename when<_, Arg0>::template result<void(Expr, State, Visitor)>::type
                          , typename when<_, Arg1>::template result<void(Expr, State, Visitor)>::type
                          , Visitor
                        >
                    impl;

                    return impl::call(
                        detail::as_lvalue(when<_, Arg0>()(expr, state, visitor))
                      , detail::as_lvalue(when<_, Arg1>()(expr, state, visitor))
                      , visitor
                    );
                }
            };

            template<typename Fun, typename Arg0, typename Arg1, typename Arg2>
            struct call<Fun(Arg0, Arg1, Arg2)> : proto::callable
            {
                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef
                        typename boost::result_of<
                            Fun(
                                typename when<_, Arg0>::template result<void(Expr, State, Visitor)>::type
                              , typename when<_, Arg1>::template result<void(Expr, State, Visitor)>::type
                              , typename when<_, Arg2>::template result<void(Expr, State, Visitor)>::type
                            )
                        >::type
                    type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    Fun f;
                    return f(
                        detail::as_lvalue(when<_, Arg0>()(expr, state, visitor))
                      , detail::as_lvalue(when<_, Arg1>()(expr, state, visitor))
                      , detail::uncv(when<_, Arg2>()(expr, state, visitor)) // HACK
                    );
                }
            };

            #if BOOST_PROTO_MAX_ARITY > 3
            #define BOOST_PP_ITERATION_PARAMS_1 (3, (4, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/call.hpp>))
            #include BOOST_PP_ITERATE()
            #endif
        }

        template<typename Fun>
        struct is_callable<transform::call<Fun> >
          : mpl::true_
        {};

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Fun BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct call<Fun(BOOST_PP_ENUM_PARAMS(N, A))> : proto::callable
        {
            template<typename Sig> struct result {};

            template<typename This, typename Expr, typename State, typename Visitor>
            struct result<This(Expr, State, Visitor)>
            {
                typedef
                    typename boost::result_of<
                        #define TMP(Z, M, DATA) typename when<_, BOOST_PP_CAT(A, M)>::template result<void(Expr, State, Visitor)>::type
                        Fun(BOOST_PP_ENUM(N, TMP, ~))
                        #undef TMP
                    >::type
                type;
            };

            template<typename Expr, typename State, typename Visitor>
            typename result<void(Expr, State, Visitor)>::type
            operator ()(Expr const &expr, State const &state, Visitor &visitor) const
            {
                Fun f;
                #define TMP(Z, M, DATA) when<_, BOOST_PP_CAT(A, M)>()(expr, state, visitor)
                return f(BOOST_PP_ENUM(N, TMP, ~));
                #undef TMP
            }
        };

    #undef N

#endif
