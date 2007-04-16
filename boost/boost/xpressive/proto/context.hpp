#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file context.hpp
    /// Definintion of context\<\>, a default evaluation context for
    /// expr\<\>::eval() that uses Boost.Typeof to deduce return types
    /// of the built-in operators.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_CONTEXT_HPP_EAN_01_08_2007
    #define BOOST_PROTO_CONTEXT_HPP_EAN_01_08_2007

    #include <boost/xpressive/proto/detail/prefix.hpp> // must be first include
    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_shifted.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/typeof/typeof.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/type_traits/is_const.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/remove_cv.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/tags.hpp>
    #include <boost/xpressive/proto/eval.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp> // must be last include

    // If we're generating doxygen documentation, hide all the nasty
    // Boost.Typeof gunk.
    #ifndef BOOST_PROTO_DOXYGEN_INVOKED
        #define BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(Nested, Expr)\
            BOOST_TYPEOF_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_and_hidden_, Nested), Expr)\
            struct Nested\
              : mpl::if_c<\
                    1==sizeof(detail::check_reference(Expr))\
                  , typename BOOST_PP_CAT(nested_and_hidden_, Nested)::type &\
                  , typename BOOST_PP_CAT(nested_and_hidden_, Nested)::type\
                >\
            {};

        #define BOOST_PROTO_TYPEOF(Expr, Type)\
            BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(BOOST_PP_CAT(nested_, Type), (Expr))\
            typedef typename BOOST_PP_CAT(nested_, Type)::type Type;
    #else
        /// INTERNAL ONLY
        ///
        #define BOOST_PROTO_TYPEOF(Expr, Type)\
            typedef detail::unspecified Type;
    #endif

    namespace boost { namespace proto
    {

        template<typename Expr, typename Context, typename Tag = typename Expr::tag_type, long Arity = Expr::arity::value>
        struct default_eval
        {};

        template<typename Expr, typename Context, long Arity = Expr::arity::value>
        struct callable_eval
        {};

        namespace detail
        {
            template<typename T> T make();

            template<typename T>
            char check_reference(T &);

            template<typename T>
            char (&check_reference(T const &))[2];

            template<typename A0, typename A1>
            struct comma_result
            {
                BOOST_PROTO_TYPEOF((detail::make<A0>(), detail::make<A1>()), type)
            };

            template<typename A0>
            struct comma_result<A0, void>
            {
                typedef void type;
            };

            template<typename A1>
            struct comma_result<void, A1>
            {
                typedef A1 type;
            };

            template<>
            struct comma_result<void, void>
            {
                typedef void type;
            };

            template<typename T, typename U = T>
            struct result_of_fixup
              : mpl::if_<is_function<T>, T *, U>
            {};

            template<typename T, typename U>
            struct result_of_fixup<T &, U>
              : result_of_fixup<T, T>
            {};

            template<typename T, typename U>
            struct result_of_fixup<T *, U>
              : result_of_fixup<T, U>
            {};

            template<typename T, typename U>
            struct result_of_fixup<T const, U>
              : result_of_fixup<T, U>
            {};

            //// Tests for result_of_fixup
            //struct bar {};
            //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar>::type>));
            //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const>::type>));
            //BOOST_MPL_ASSERT((is_same<bar,        result_of_fixup<bar &>::type>));
            //BOOST_MPL_ASSERT((is_same<bar const,  result_of_fixup<bar const &>::type>));
            //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(*)()>::type>));
            //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const)()>::type>));
            //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(* const &)()>::type>));
            //BOOST_MPL_ASSERT((is_same<void(*)(),  result_of_fixup<void(&)()>::type>));

            struct dont_care
            {
                template<typename T>
                dont_care(T const &)
                {}
            };

        #if BOOST_WORKAROUND(BOOST_MSVC, == 1400)
            template<typename T> T &ref_(T &t);
            template<typename T> T const &ref_(T const &t);
            #define BOOST_PROTO_REF(x) detail::ref_(x)
        #else
            #define BOOST_PROTO_REF(x) x
        #endif
        }

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_UNARY_OP_RESULT(Op, Tag)\
        template<typename Expr, typename Context>\
        struct default_eval<Expr, Context, Tag, 1>\
        {\
        private:\
            static Expr &sexpr;\
            static Context &sctx;\
        public:\
            BOOST_PROTO_TYPEOF(Op proto::eval(BOOST_PROTO_REF(proto::arg_c<0>(sexpr)), sctx), result_type)\
            result_type operator()(Expr &expr, Context &ctx) const\
            {\
                return Op proto::eval(proto::arg_c<0>(expr), ctx);\
            }\
        };\
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_BINARY_OP_RESULT(Op, Tag)\
        template<typename Expr, typename Context>\
        struct default_eval<Expr, Context, Tag, 2>\
        {\
        private:\
            static Expr &sexpr;\
            static Context &sctx;\
        public:\
            BOOST_PROTO_TYPEOF(proto::eval(BOOST_PROTO_REF(proto::arg_c<0>(sexpr)), sctx) Op proto::eval(BOOST_PROTO_REF(proto::arg_c<1>(sexpr)), sctx), result_type)\
            result_type operator()(Expr &expr, Context &ctx) const\
            {\
                return proto::eval(proto::arg_c<0>(expr), ctx) Op proto::eval(proto::arg_c<1>(expr), ctx);\
            }\
        };\
        /**/

        BOOST_PROTO_UNARY_OP_RESULT(+, proto::tag::unary_plus)
        BOOST_PROTO_UNARY_OP_RESULT(-, proto::tag::unary_minus)
        BOOST_PROTO_UNARY_OP_RESULT(*, proto::tag::unary_star)
        BOOST_PROTO_UNARY_OP_RESULT(~, proto::tag::complement)
        BOOST_PROTO_UNARY_OP_RESULT(&, proto::tag::address_of)
        BOOST_PROTO_UNARY_OP_RESULT(!, proto::tag::logical_not)
        BOOST_PROTO_UNARY_OP_RESULT(++, proto::tag::pre_inc)
        BOOST_PROTO_UNARY_OP_RESULT(--, proto::tag::pre_dec)

        BOOST_PROTO_BINARY_OP_RESULT(<<, proto::tag::left_shift)
        BOOST_PROTO_BINARY_OP_RESULT(>>, proto::tag::right_shift)
        BOOST_PROTO_BINARY_OP_RESULT(*, proto::tag::multiply)
        BOOST_PROTO_BINARY_OP_RESULT(/, proto::tag::divide)
        BOOST_PROTO_BINARY_OP_RESULT(%, proto::tag::modulus)
        BOOST_PROTO_BINARY_OP_RESULT(+, proto::tag::add)
        BOOST_PROTO_BINARY_OP_RESULT(-, proto::tag::subtract)
        BOOST_PROTO_BINARY_OP_RESULT(<, proto::tag::less)
        BOOST_PROTO_BINARY_OP_RESULT(>, proto::tag::greater)
        BOOST_PROTO_BINARY_OP_RESULT(<=, proto::tag::less_equal)
        BOOST_PROTO_BINARY_OP_RESULT(>=, proto::tag::greater_equal)
        BOOST_PROTO_BINARY_OP_RESULT(==, proto::tag::equal)
        BOOST_PROTO_BINARY_OP_RESULT(!=, proto::tag::not_equal)
        BOOST_PROTO_BINARY_OP_RESULT(||, proto::tag::logical_or)
        BOOST_PROTO_BINARY_OP_RESULT(&&, proto::tag::logical_and)
        BOOST_PROTO_BINARY_OP_RESULT(&, proto::tag::bitwise_and)
        BOOST_PROTO_BINARY_OP_RESULT(|, proto::tag::bitwise_or)
        BOOST_PROTO_BINARY_OP_RESULT(^, proto::tag::bitwise_xor)
        BOOST_PROTO_BINARY_OP_RESULT(->*, proto::tag::mem_ptr)

        BOOST_PROTO_BINARY_OP_RESULT(=, proto::tag::assign)
        BOOST_PROTO_BINARY_OP_RESULT(<<=, proto::tag::left_shift_assign)
        BOOST_PROTO_BINARY_OP_RESULT(>>=, proto::tag::right_shift_assign)
        BOOST_PROTO_BINARY_OP_RESULT(*=, proto::tag::multiply_assign)
        BOOST_PROTO_BINARY_OP_RESULT(/=, proto::tag::divide_assign)
        BOOST_PROTO_BINARY_OP_RESULT(%=, proto::tag::modulus_assign)
        BOOST_PROTO_BINARY_OP_RESULT(+=, proto::tag::add_assign)
        BOOST_PROTO_BINARY_OP_RESULT(-=, proto::tag::subtract_assign)
        BOOST_PROTO_BINARY_OP_RESULT(&=, proto::tag::bitwise_and_assign)
        BOOST_PROTO_BINARY_OP_RESULT(|=, proto::tag::bitwise_or_assign)
        BOOST_PROTO_BINARY_OP_RESULT(^=, proto::tag::bitwise_xor_assign)

        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::terminal, 1>
        {
            typedef
                typename mpl::if_<
                    is_const<Expr>
                  , typename proto::result_of::arg<Expr>::const_reference
                  , typename proto::result_of::arg<Expr>::reference
                >::type
            result_type;

            result_type operator()(Expr &expr, Context &) const
            {
                return proto::arg(expr);
            }
        };

        // Handle post-increment specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::post_inc, 1>
        {
        private:
            static Expr &sexpr;
            static Context &sctx;
        public:
            BOOST_PROTO_TYPEOF(proto::eval(BOOST_PROTO_REF(proto::arg_c<0>(sexpr)), sctx) ++, result_type)
            result_type operator()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::arg_c<0>(expr), ctx) ++;
            }
        };

        // Handle post-decrement specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::post_dec, 1>
        {
        private:
            static Expr &sexpr;
            static Context &sctx;
        public:
            BOOST_PROTO_TYPEOF(proto::eval(BOOST_PROTO_REF(proto::arg_c<0>(sexpr)), sctx) --, result_type)
            result_type operator()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::arg_c<0>(expr), ctx) --;
            }
        };

        // Handle subscript specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::subscript, 2>
        {
        private:
            static Expr &sexpr;
            static Context &sctx;
        public:
            BOOST_PROTO_TYPEOF(proto::eval(BOOST_PROTO_REF(proto::arg_c<0>(sexpr)), sctx)[proto::eval(BOOST_PROTO_REF(proto::arg_c<1>(sexpr)), sctx)], result_type)
            result_type operator()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::arg_c<0>(expr), ctx)[proto::eval(proto::arg_c<1>(expr), ctx)];
            }
        };

        // Handle comma specially.
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::comma, 2>
        {
            typedef typename proto::result_of::eval<typename proto::result_of::arg_c<Expr, 0>::type, Context>::type arg0_type;
            typedef typename proto::result_of::eval<typename proto::result_of::arg_c<Expr, 1>::type, Context>::type arg1_type;
            typedef typename detail::comma_result<arg0_type, arg1_type>::type result_type;
            result_type operator()(Expr &expr, Context &ctx) const
            {
                return proto::eval(proto::arg_c<0>(expr), ctx), proto::eval(proto::arg_c<1>(expr), ctx);
            }
        };

    #define BOOST_PROTO_ARG_N_TYPE(Z, N, Expr)\
        typename proto::result_of::arg_c<Expr, N>::const_reference

    #define BOOST_PROTO_ARG_N(Z, N, expr)\
        proto::arg_c<N>(expr)

    #define BOOST_PROTO_EVAL_N_TYPE(Z, N, Data)\
        typename proto::result_of::eval<\
            typename proto::result_of::arg_c<BOOST_PP_TUPLE_ELEM(2, 0, Data), N>::type\
          , BOOST_PP_TUPLE_ELEM(2, 1, Data)\
        >::type

    #define BOOST_PROTO_EVAL_N(Z, N, Data)\
        proto::eval(proto::arg_c<N>(BOOST_PP_TUPLE_ELEM(2, 0, Data)), BOOST_PP_TUPLE_ELEM(2, 1, Data))

    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/context.hpp>))
    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_ARG_N_TYPE
    #undef BOOST_PROTO_ARG_N
    #undef BOOST_PROTO_EVAL_N_TYPE
    #undef BOOST_PROTO_EVAL_N

        /// default_context
        ///
        struct default_context
        {
            /// default_context::eval
            ///
            template<typename Expr>
            struct eval
              : default_eval<Expr, default_context>
            {};
        };

        /// callable_context
        ///
        template<typename Context>
        struct callable_context
        {
            /// callable_context::eval
            ///
            template<typename Expr>
            struct eval
              : callable_eval<Expr, Context>
            {};
        };

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        // Handle function specially
        template<typename Expr, typename Context>
        struct default_eval<Expr, Context, proto::tag::function, N>
        {
            typedef
                typename detail::result_of_fixup<
                    BOOST_PROTO_EVAL_N_TYPE(1, 0, (Expr, Context))
                >::type
            function_type;

            typedef
                typename boost::result_of<
                    function_type(
                        BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_EVAL_N_TYPE, (Expr, Context))
                    )
                >::type
            result_type;

            result_type operator ()(Expr &expr, Context &context) const
            {
                return BOOST_PROTO_EVAL_N(1, 0, (expr, context))(
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_EVAL_N, (expr, context))
                );
            }
        };

        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, N>
        {
        private:
            /// INTERNAL ONLY
            ///
            typedef typename remove_cv<Context>::type context_type;
            /// INTERNAL ONLY
            ///
            struct inner_context
              : context_type
            {
                inner_context();
                struct private_type_ { private_type_ const &operator,(int) const { return *this; } };
                typedef private_type_ const &(*pointer_to_function)(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(N), detail::dont_care BOOST_PP_INTERCEPT));
                operator pointer_to_function() const;
            };

        public:
            typedef
                typename boost::result_of<
                    Context(
                        typename Expr::tag_type
                        BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_ARG_N_TYPE, Expr)
                    )
                >::type
            result_type;

            result_type operator ()(Expr &expr, Context &context) const
            {
                BOOST_STATIC_CONSTANT(bool, value =
                    (
                        sizeof(yes_type) ==
                        sizeof(
                            callable_eval::check(
                                (static_cast<inner_context &>(const_cast<context_type &>(context))(
                                    typename Expr::tag_type()
                                    BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_ARG_N, expr)
                                ), 0)
                            )
                    )));
                return (*this)(expr, context, mpl::bool_<value>());
            }

        private:

            typedef char yes_type;
            typedef char (&no_type)[2];
            template<typename T> static yes_type check(T const &);
            static no_type check(typename inner_context::private_type_ const &);

            result_type operator ()(Expr &expr, Context &context, mpl::true_) const
            {
                return context(
                    typename Expr::tag_type()
                    BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_ARG_N, expr)
                );
            }

            result_type operator ()(Expr &expr, Context &context, mpl::false_) const
            {
                return default_eval<Expr, Context>()(expr, context);
            }
        };

    #undef N

#endif
