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
    #include <boost/mpl/lambda.hpp>
    #include <boost/mpl/apply_wrap.hpp>
    #include <boost/type_traits/is_function.hpp>
    #include <boost/type_traits/remove_pointer.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto { namespace transform
    {
        namespace detail
        {
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

            template<typename Result, typename Expr, typename Lambda = typename mpl::lambda<Result>::type>
            struct apply_if_
              : mpl::apply_wrap1<Lambda, Expr>
            {};

            template<typename Result, typename Expr>
            struct apply_if_<Result, Expr, Result>
              : nested_type<Result>
            {};

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
        }

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/transform/construct.hpp>))
        #include BOOST_PP_ITERATE()

    }}}

    #endif

#else

    #define N BOOST_PP_ITERATION()

        template<typename Grammar, typename Result BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Arg)>
        struct construct<Grammar, Result(BOOST_PP_ENUM_PARAMS(N, Arg))>
          : Grammar
        {
            template<typename Expr, typename State, typename Visitor>
            struct apply
              : detail::apply_if_<Result, typename Grammar::template apply<Expr, State, Visitor>::type>
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
