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

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/facilities/apply.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/typeof/typeof.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/type_traits/is_same.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/add_const.hpp>
    #include <boost/type_traits/add_reference.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/tags.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {
        namespace detail
        {
            template<typename T> T make();

            template<typename T>
            char check_reference(T &);

            template<typename T>
            char (&check_reference(T const &))[2];

            template<typename T>
            struct as_param
              : add_reference<typename add_const<T>::type>
            {};

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
        }

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(Nested, Expr)\
        BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested_and_hidden, Expr)\
        struct Nested\
          : mpl::if_c<\
                1==sizeof(detail::check_reference(Expr))\
              , typename nested_and_hidden::type &\
              , typename nested_and_hidden::type\
            >\
        {};\
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_TYPEOF_UNARY(Op, Arg0, Type)\
        BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (Op detail::make<Arg0>()))\
        typedef typename nested::type Type;\
        /**/

        /// INTERNAL ONLY
        ///
    #define BOOST_PROTO_TYPEOF_BINARY(Op, Arg0, ARG1, Type)\
        BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<Arg0>() Op detail::make<Arg1>()))\
        typedef typename nested::type Type;\
        /**/

        template<typename Derived>
        struct context
        {
            typedef typename mpl::if_<
                is_same<Derived, void>
              , context
              , Derived
            >::type derived_type;

            derived_type &cast()
            {
                return *static_cast<derived_type *>(this);
            }

            // BUGBUG Doxygen can't make any sense of the nested result<> templates
        #ifndef BOOST_PROTO_DOXYGEN_INVOKED

            template<typename Sig>
            struct result;

            template<typename This, typename A0>
            struct result<This(proto::tag::terminal, A0 &)>
            {
                typedef A0 &type;
            };

        #define BOOST_PROTO_UNARY_OP_RESULT(Op, Tag)\
            template<typename This, typename A0>\
            struct result<This(Tag, A0 &)>\
            {\
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;\
                BOOST_PROTO_TYPEOF_UNARY(Op, eval_type0, type)\
                static type call(typename detail::as_param<eval_type0>::type a0)\
                {\
                    return Op a0;\
                }\
            };\
            /**/

        #define BOOST_PROTO_BINARY_OP_RESULT(Op, Tag)\
            template<typename This, typename A0, typename A1>\
            struct result<This(Tag, A0 &, A1 &)>\
            {\
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;\
                typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;\
                BOOST_PROTO_TYPEOF_BINARY(Op, eval_type0, eval_type1, type)\
                static type\
                    call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)\
                {\
                    return a0 Op a1;\
                }\
            };\
            /**/

            // GCC will ICE if we try to evaluate the typeof an op= expression, like (i += 1)
        #if !BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4))
            #define BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(Op, Tag)\
                BOOST_PROTO_BINARY_OP_RESULT(Op, Tag)
        #else
            #define BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(Op, Tag)\
                template<typename This, typename A0, typename A1>\
                struct result<This(Tag, A0 &, A1 &)>\
                {\
                    typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;\
                    typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;\
                    typedef eval_type0 type;\
                    static type\
                        call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)\
                    {\
                        return a0 Op a1;\
                    }\
                };\
                /**/
        #endif

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

            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(<<=, proto::tag::left_shift_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(>>=, proto::tag::right_shift_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(*=, proto::tag::multiply_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(/=, proto::tag::divide_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(%=, proto::tag::modulus_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(+=, proto::tag::add_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(-=, proto::tag::subtract_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(&=, proto::tag::bitwise_and_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(|=, proto::tag::bitwise_or_assign)
            BOOST_PROTO_BINARY_OP_ASSIGN_RESULT(^=, proto::tag::bitwise_xor_assign)

        #undef BOOST_PROTO_UNARY_OP_RESULT
        #undef BOOST_PROTO_BINARY_OP_RESULT
        #undef BOOST_PROTO_BINARY_OP_ASSIGN_RESULT

            // Handle comma specially.
            template<typename This, typename A0, typename A1>
            struct result<This(proto::tag::comma, A0 &, A1 &)>
            {
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
                typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;
                BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>(), detail::make<eval_type1>()))
                typedef typename nested::type type;
                static type call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)
                {
                    return a0, a1;
                }
            };

            // Handle post-increment specially.
            template<typename This, typename A0>
            struct result<This(proto::tag::post_inc, A0 &)>
            {
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
                BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() ++))
                typedef typename nested::type type;
                static type call(typename detail::as_param<eval_type0>::type a0)
                {
                    return a0 ++;
                }
            };

            // Handle post-decrement specially.
            template<typename This, typename A0>
            struct result<This(proto::tag::post_dec, A0 &)>
            {
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
                BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() --))
                typedef typename nested::type type;
                static type call(typename detail::as_param<eval_type0>::type a0)
                {
                    return a0 --;
                }
            };

            // Handle subscript specially.
            template<typename This, typename A0, typename A1>
            struct result<This(proto::tag::subscript, A0 &, A1 &)>
            {
                typedef typename proto::result_of::eval<A0, derived_type>::type eval_type0;
                typedef typename proto::result_of::eval<A1, derived_type>::type eval_type1;
                BOOST_PROTO_DECLTYPE_NESTED_TYPEDEF_TPL(nested, (detail::make<eval_type0>() [ detail::make<eval_type1>() ] ))
                typedef typename nested::type type;
                static type call(typename detail::as_param<eval_type0>::type a0, typename detail::as_param<eval_type1>::type a1)
                {
                    return a0 [ a1 ];
                }
            };

        #else // BOOST_PROTO_DOXYGEN_INVOKED

            /// Calculates the return type of context\<\>::operator()
            ///
            template<typename Sig>
            struct result
            {
                typedef detail::unspecified type;
            };

        #endif // BOOST_PROTO_DOXYGEN_INVOKED

            template<typename A0>
            A0 &
            operator()(proto::tag::terminal, A0 &a0)
            {
                return a0;
            }

        #define BOOST_PROTO_ARG(z, n, data)\
            typedef\
                typename proto::result_of::eval<BOOST_PP_CAT(A, n), derived_type>::type\
            BOOST_PP_CAT(eval_type, n);\
            /**/

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/context.hpp>))
        #include BOOST_PP_ITERATE()
        #undef BOOST_PROTO_ARG

        };

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            // BUGBUG Doxygen can't make any sense of the nested result<> templates
        #ifndef BOOST_PROTO_DOXYGEN_INVOKED
            template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
            struct result<This(proto::tag::function BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>
            {
                BOOST_PP_REPEAT(N, BOOST_PROTO_ARG, ~)
                typedef typename detail::result_of_fixup<eval_type0>::type function_type;
                typedef typename boost::result_of<function_type( BOOST_PP_ENUM_SHIFTED_PARAMS(N, eval_type) )>::type type;
                static type call(
                    BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::as_param<eval_type, >::type a)
                )
                {
                    return a0 ( BOOST_PP_ENUM_SHIFTED_PARAMS(N, a) );
                }
            };
        #endif

            template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
            typename result<derived_type(Tag BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>::type
            operator()(Tag BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, A, & a))
            {
                return result<derived_type(Tag, BOOST_PP_ENUM_BINARY_PARAMS(N, A, & BOOST_PP_INTERCEPT))>::call(
                    BOOST_PP_ENUM_BINARY_PARAMS(N, a, .eval(this->cast()) BOOST_PP_INTERCEPT)
                );
            }

    #undef N

#endif
