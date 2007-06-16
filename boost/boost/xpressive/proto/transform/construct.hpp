#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct.hpp
    /// For constructing an arbitrary type from a bunch of transforms.
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_CONSTRUCT_HPP_EAN_12_26_2006
    #define BOOST_PROTO_TRANSFORM_CONSTRUCT_HPP_EAN_12_26_2006

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/remove_pointer.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto { namespace transform
    {
        namespace detail
        {
            using proto::detail::is_placeholder_expression;

            template<typename T, bool HasType = mpl::aux::has_type<T>::value>
            struct nested_type
            {
                typedef typename T::type type;
            };

            template<typename T>
            struct nested_type<T, false>
            {
                typedef T type;
            };

            template<typename Arg, bool IsFunction = is_function<typename remove_pointer<Arg>::type>::value>
            struct as_transform
            {
                typedef Arg type;
            };

            template<typename Arg>
            struct as_transform<Arg, true>
            {
                typedef construct<_, typename remove_pointer<Arg>::type> type;
            };

            template<typename R, typename Expr, typename State, typename Visitor
                     BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(long Arity = mpl::aux::template_arity<R>::value)>
            struct apply_aux2_;

            template<typename R, typename Expr, typename State, typename Visitor,
                     bool IsPlaceholder = is_placeholder_expression<R>::value>
            struct apply_aux_
            {
                typedef R type;
            };

            template<typename R, typename Expr, typename State, typename Visitor>
            struct apply_aux_<R, Expr, State, Visitor, true>
              : apply_aux2_<R, Expr, State, Visitor>
            {};

            template<typename R, typename Expr, typename State, typename Visitor, typename EnableIf = void>
            struct apply_
              : apply_aux_<R, Expr, State, Visitor>
            {};

            template<typename R, typename Expr, typename State, typename Visitor>
            struct apply_<R, Expr, State, Visitor, typename R::proto_is_placeholder_>
              : nested_type<typename R::template apply<Expr, State, Visitor>::type>
            {};
        }

        #define BOOST_PROTO_APPLY_(Z, N, DATA)                                                      \
            typename apply_<BOOST_PP_CAT(DATA, N), Expr, State, Visitor>::type                      \
            /**/

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/construct.hpp>))
        #include BOOST_PP_ITERATE()

        #undef BOOST_PROTO_APPLY_

    }}}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        #if N > 0
        namespace detail
        {
            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G),
                typename Expr, typename State, typename Visitor
            >
            struct apply_aux2_<T<BOOST_PP_ENUM_PARAMS(N, G)>, Expr, State, Visitor BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(N)>
              : nested_type<T<BOOST_PP_ENUM(N, BOOST_PROTO_APPLY_, G)> >
            {};
        }
        #endif

        template<typename Grammar, typename Result BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Arg)>
        struct construct<Grammar, Result(BOOST_PP_ENUM_PARAMS(N, Arg))>
          : Grammar
        {
            template<typename Expr, typename State, typename Visitor>
            struct apply
              : detail::apply_<Result, typename Grammar::template apply<Expr, State, Visitor>::type, State, Visitor>
            {};

            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call(Expr const &expr, State const &state, Visitor &visitor)
            {
                return construct::call_(expr, state, visitor, is_expr<typename apply<Expr, State, Visitor>::type>());
            }

        private:
            /// INTERNAL ONLY
            ///
            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call_(Expr const &expr, State const &state, Visitor &visitor, mpl::true_)
            {
                typename Grammar::template apply<Expr, State, Visitor>::type const &expr2
                    = Grammar::call(expr, state, visitor);
                typename apply<Expr, State, Visitor>::type that = {
                    BOOST_PP_ENUM_BINARY_PARAMS(N, detail::as_transform<Arg, >::type::call(expr2, state, visitor) BOOST_PP_INTERCEPT)
                };
                return that;
            }

            /// INTERNAL ONLY
            ///
            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call_(Expr const &expr, State const &state, Visitor &visitor, mpl::false_)
            {
                typename Grammar::template apply<Expr, State, Visitor>::type const &expr2
                    = Grammar::call(expr, state, visitor);
                return typename apply<Expr, State, Visitor>::type(
                    BOOST_PP_ENUM_BINARY_PARAMS(N, detail::as_transform<Arg, >::type::call(expr2, state, visitor) BOOST_PP_INTERCEPT)
                );
            }
        };

    #undef N

#endif
