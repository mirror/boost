#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file traits.hpp
    /// Contains definitions for arg\<\>, arg_c\<\>, left\<\>,
    /// right\<\>, tag\<\>, and the helper functions arg(), arg_c(),
    /// left() and right().
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
    #define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/repeat_from_to.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/ref.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/or.hpp>
    #include <boost/mpl/bool.hpp>
    #include <boost/static_assert.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/type_traits/is_array.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/remove_const.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/ref.hpp>
    #include <boost/xpressive/proto/args.hpp>
    #include <boost/xpressive/proto/tags.hpp>
    #include <boost/xpressive/proto/transform/pass_through.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    #if BOOST_WORKAROUND( BOOST_MSVC, == 1310 )
        #define BOOST_PROTO_IS_ARRAY_(T) boost::is_array<typename boost::remove_const<T>::type>
    #else
        #define BOOST_PROTO_IS_ARRAY_(T) boost::is_array<T>
    #endif

    namespace boost { namespace proto
    {

        // is_ref
        template<typename T, typename EnableIf>
        struct is_ref
          : mpl::false_
        {};

        template<typename T>
        struct is_ref<T, typename T::is_boost_proto_ref_>
          : mpl::true_
        {};

        // is_expr
        template<typename T, typename EnableIf>
        struct is_expr
          : mpl::false_
        {};

        template<typename T>
        struct is_expr<T, typename T::is_boost_proto_expr_>
          : mpl::true_
        {};

        namespace result_of
        {
            // as_expr
            template<typename T, typename EnableIf>
            struct as_expr
            {
                typedef typename mpl::if_<
                    mpl::or_<BOOST_PROTO_IS_ARRAY_(T), is_function<T> >
                  , T &
                  , typename remove_cv<T>::type
                >::type arg0_type;

                typedef expr<proto::tag::terminal, args1<arg0_type> > type;
                typedef type result_type;

            #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
                template<typename T2>
                static result_type call(T2 &t)
                {
                    return type::make(t);
                }
            #else
                static result_type call(T &t)
                {
                    return type::make(t);
                }
            #endif
            };

            template<typename T>
            struct as_expr<T, typename T::is_boost_proto_expr_>
            {
                typedef typename T::boost_proto_expr_type_ type;
                typedef T &result_type;

            #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
                template<typename T2>
                static result_type call(T2 &t)
                {
                    return t;
                }
            #else
                static result_type call(T &t)
                {
                    return t;
                }
            #endif
            };

            // as_arg
            template<typename T, typename EnableIf>
            struct as_arg
            {
                typedef expr<proto::tag::terminal, args1<T &> > type;
            };

            template<typename T>
            struct as_arg<T, typename T::is_boost_proto_expr_>
            {
                typedef ref<T> type;
            };

            template<typename Expr, typename N>
            struct arg
              : arg_c<Expr, N::value>
            {};

            // left
                // BUGBUG this forces the instantiation of Expr. Couldn't we
                // partially specialize left<> on expr< T, A > and 
                // ref< expr< T, A > > and return A::arg0 ?
            template<typename Expr>
            struct left
              : unref<typename Expr::arg0_type>
            {};

            // right
            template<typename Expr>
            struct right
              : unref<typename Expr::arg1_type>
            {};

        }

        namespace detail
        {
            template<typename T, typename EnableIf = void>
            struct if_vararg {};

            template<typename T>
            struct if_vararg<T, typename T::boost_proto_is_vararg_>
              : T
            {};
        }

        // terminal
        template<typename T>
        struct terminal : has_identity_transform
        {
            terminal();
            typedef expr<proto::tag::terminal, args1<T> > type;
            typedef proto::tag::terminal tag_type;
            typedef T arg0_type;
        };

        // unary_expr
        template<typename Tag, typename T>
        struct unary_expr : has_pass_through_transform<unary_expr<Tag, T> >
        {
            unary_expr();
            typedef expr<Tag, args1<T> > type;
            typedef Tag tag_type;
            typedef T arg0_type;
        };

        // binary_expr
        template<typename Tag, typename T, typename U>
        struct binary_expr : has_pass_through_transform<binary_expr<Tag, T, U> >
        {
            binary_expr();
            typedef expr<Tag, args2<T, U> > type;
            typedef Tag tag_type;
            typedef T arg0_type;
            typedef U arg1_type;
        };

    #define BOOST_PROTO_UNARY_GENERATOR(Name)\
        template<typename T>\
        struct Name : has_pass_through_transform<Name<T> >\
        {\
            Name();\
            typedef expr<proto::tag::Name, args1<T> > type;\
            typedef proto::tag::Name tag_type;\
            typedef T arg0_type;\
        };\
        /**/

    #define BOOST_PROTO_BINARY_GENERATOR(Name)\
        template<typename T, typename U>\
        struct Name : has_pass_through_transform<Name<T, U> >\
        {\
            Name();\
            typedef expr<proto::tag::Name, args2<T, U> > type;\
            typedef proto::tag::Name tag_type;\
            typedef T arg0_type;\
            typedef U arg1_type;\
        };\
        /**/

        BOOST_PROTO_UNARY_GENERATOR(unary_plus)
        BOOST_PROTO_UNARY_GENERATOR(unary_minus)
        BOOST_PROTO_UNARY_GENERATOR(unary_star)
        BOOST_PROTO_UNARY_GENERATOR(complement)
        BOOST_PROTO_UNARY_GENERATOR(address_of)
        BOOST_PROTO_UNARY_GENERATOR(logical_not)
        BOOST_PROTO_UNARY_GENERATOR(pre_inc)
        BOOST_PROTO_UNARY_GENERATOR(pre_dec)
        BOOST_PROTO_UNARY_GENERATOR(post_inc)
        BOOST_PROTO_UNARY_GENERATOR(post_dec)

        BOOST_PROTO_BINARY_GENERATOR(left_shift)
        BOOST_PROTO_BINARY_GENERATOR(right_shift)
        BOOST_PROTO_BINARY_GENERATOR(multiply)
        BOOST_PROTO_BINARY_GENERATOR(divide)
        BOOST_PROTO_BINARY_GENERATOR(modulus)
        BOOST_PROTO_BINARY_GENERATOR(add)
        BOOST_PROTO_BINARY_GENERATOR(subtract)
        BOOST_PROTO_BINARY_GENERATOR(less)
        BOOST_PROTO_BINARY_GENERATOR(greater)
        BOOST_PROTO_BINARY_GENERATOR(less_equal)
        BOOST_PROTO_BINARY_GENERATOR(greater_equal)
        BOOST_PROTO_BINARY_GENERATOR(equal)
        BOOST_PROTO_BINARY_GENERATOR(not_equal)
        BOOST_PROTO_BINARY_GENERATOR(logical_or)
        BOOST_PROTO_BINARY_GENERATOR(logical_and)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_and)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_or)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_xor)
        BOOST_PROTO_BINARY_GENERATOR(comma)
        BOOST_PROTO_BINARY_GENERATOR(mem_ptr)

        BOOST_PROTO_BINARY_GENERATOR(assign)
        BOOST_PROTO_BINARY_GENERATOR(left_shift_assign)
        BOOST_PROTO_BINARY_GENERATOR(right_shift_assign)
        BOOST_PROTO_BINARY_GENERATOR(multiply_assign)
        BOOST_PROTO_BINARY_GENERATOR(divide_assign)
        BOOST_PROTO_BINARY_GENERATOR(modulus_assign)
        BOOST_PROTO_BINARY_GENERATOR(add_assign)
        BOOST_PROTO_BINARY_GENERATOR(subtract_assign)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_and_assign)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_or_assign)
        BOOST_PROTO_BINARY_GENERATOR(bitwise_xor_assign)
        BOOST_PROTO_BINARY_GENERATOR(subscript)

    #undef BOOST_PROTO_UNARY_GENERATOR
    #undef BOOST_PROTO_BINARY_GENERATOR

        // tag_of
        template<typename Expr>
        struct tag_of
        {
            typedef typename Expr::tag_type type;
        };

        // id
        template<typename Expr>
        struct id
          : result_of::deep_copy<Expr>
        {};

    #define BOOST_PROTO_ARG(z, n, data)\
        typedef BOOST_PP_CAT(data, n) BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);\
        /**/

    #define BOOST_PROTO_ARG_N_TYPE(z, n, data)\
        typename proto::result_of::unref<\
            typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type)\
        >::const_reference\
        /**/

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/traits.hpp>))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_1

    #undef BOOST_PROTO_ARG
    #undef BOOST_PROTO_ARG_N_TYPE

        namespace op
        {
            struct as_expr
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename T>
                struct result<This(T)>
                  : result_of::as_expr<typename remove_reference<T>::type>
                {};

                template<typename T>
                typename result_of::as_expr<T>::result_type operator()(T &t) const
                {
                    return result_of::as_expr<T>::call(t);
                }

                template<typename T>
                typename result_of::as_expr<T const>::result_type operator()(T const &t) const
                {
                    return result_of::as_expr<T const>::call(t);
                }
            };

            struct as_arg
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename T>
                struct result<This(T)>
                  : result_of::as_arg<typename remove_reference<T>::type>
                {};

                template<typename T>
                typename result_of::as_arg<T>::type operator()(T &t) const
                {
                    typename result_of::as_arg<T>::type that = {t};
                    return that;
                }

                template<typename T>
                typename result_of::as_arg<T const>::type operator()(T const &t) const
                {
                    typename result_of::as_arg<T const>::type that = {t};
                    return that;
                }
            };

            template<long N>
            struct arg_c
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : result_of::arg_c<typename detail::remove_cv_ref<Expr>::type, N>
                {};

                template<typename Expr>
                typename result_of::arg_c<Expr, N>::reference operator()(Expr &expr) const
                {
                    return result_of::arg_c<Expr, N>::call(expr);
                }

                template<typename Expr>
                typename result_of::arg_c<Expr, N>::const_reference operator()(Expr const &expr) const
                {
                    return result_of::arg_c<Expr, N>::call(expr);
                }
            };

            template<typename N>
            struct arg
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : result_of::arg<typename detail::remove_cv_ref<Expr>::type, N>
                {};

                template<typename Expr>
                typename result_of::arg<Expr, N>::reference operator()(Expr &expr) const
                {
                    return result_of::arg<Expr, N>::call(expr);
                }

                template<typename Expr>
                typename result_of::arg<Expr, N>::const_reference operator()(Expr const &expr) const
                {
                    return result_of::arg<Expr, N>::call(expr);
                }
            };

            struct left
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : result_of::left<typename detail::remove_cv_ref<Expr>::type>
                {};

                template<typename Expr>
                typename result_of::left<Expr>::reference operator()(Expr &expr) const
                {
                    return proto::unref(expr.cast().arg0);
                }

                template<typename Expr>
                typename result_of::left<Expr>::const_reference operator()(Expr const &expr) const
                {
                    return proto::unref(expr.cast().arg0);
                }
            };

            struct right
            {
                template<typename Sig>
                struct result {};

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : result_of::right<typename detail::remove_cv_ref<Expr>::type>
                {};

                template<typename Expr>
                typename result_of::right<Expr>::reference operator()(Expr &expr) const
                {
                    return proto::unref(expr.cast().arg1);
                }

                template<typename Expr>
                typename result_of::right<Expr>::const_reference operator()(Expr const &expr) const
                {
                    return proto::unref(expr.cast().arg1);
                }
            };

        }

        op::as_expr const as_expr = {};
        op::as_arg const as_arg = {};
        op::left const left = {};
        op::right const right = {};

        /// arg
        ///
        template<typename Expr>
        typename result_of::unref<typename Expr::type::arg0_type>::reference
        arg(Expr &expr BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
        {
            return proto::unref(expr.cast().arg0);
        };

        /// \overload
        ///
        template<typename Expr>
        typename result_of::unref<typename Expr::type::arg0_type>::const_reference
        arg(Expr const &expr)
        {
            return proto::unref(expr.cast().arg0);
        };

        /// \overload
        ///
        template<typename N, typename Expr>
        typename result_of::arg<Expr, N>::reference 
        arg(Expr &expr BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
        {
            return result_of::arg<Expr, N>::call(expr);
        };

        /// \overload
        ///
        template<typename N, typename Expr>
        typename result_of::arg<Expr, N>::const_reference 
        arg(Expr const &expr)
        {
            return result_of::arg<Expr, N>::call(expr);
        };

        /// arg_c
        ///
        template<long N, typename Expr>
        typename result_of::arg_c<Expr, N>::reference
        arg_c(Expr &expr BOOST_PROTO_DISABLE_IF_IS_CONST(Expr))
        {
            return result_of::arg_c<Expr, N>::call(expr);
        };

        /// \overload
        ///
        template<long N, typename Expr>
        typename result_of::arg_c<Expr, N>::const_reference arg_c(Expr const &expr)
        {
            return result_of::arg_c<Expr, N>::call(expr);
        };

    }}

    #endif

#else // PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()
    #if N > 0
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        struct function<
            BOOST_PP_ENUM_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT), void
        >
          : has_pass_through_transform<
                function<
                    BOOST_PP_ENUM_PARAMS(N, A)
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT), void
                >
            >
        {
            typedef expr<proto::tag::function, BOOST_PP_CAT(args, N)<BOOST_PP_ENUM_PARAMS(N, A)> > type;
            typedef proto::tag::function tag_type;
            BOOST_PP_REPEAT(N, BOOST_PROTO_ARG, A)
            BOOST_PP_REPEAT_FROM_TO(N, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_ARG, detail::if_vararg<BOOST_PP_CAT(A, BOOST_PP_DEC(N))> BOOST_PP_INTERCEPT)
        };

        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct nary_expr<
            Tag
            BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT), void
        >
          : has_pass_through_transform<
                nary_expr<
                    Tag
                    BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
                    BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT), void
                >
            >
        {
            typedef expr<Tag, BOOST_PP_CAT(args, N)<BOOST_PP_ENUM_PARAMS(N, A)> > type;
            typedef Tag tag_type;
            BOOST_PP_REPEAT(N, BOOST_PROTO_ARG, A)
            BOOST_PP_REPEAT_FROM_TO(N, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_ARG, detail::if_vararg<BOOST_PP_CAT(A, BOOST_PP_DEC(N))> BOOST_PP_INTERCEPT)
        };
    #endif

        namespace result_of
        {
            template<typename Expr>
            struct arg_c<Expr, N>
              : unref<typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, N), _type)>
            {
                static typename arg_c::reference call(Expr &expr)
                {
                    return proto::unref(expr.cast().BOOST_PP_CAT(arg, N));
                }

                static typename arg_c::const_reference call(Expr const &expr)
                {
                    return proto::unref(expr.cast().BOOST_PP_CAT(arg, N));
                }
            };

            template<typename Expr>
            struct arg_c<Expr const, N>
              : arg_c<Expr, N>
            {};
        }

    #undef N

#endif
