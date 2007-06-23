#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file callable.hpp
    /// Definintion of callable_context\<\>, an evaluation context for
    /// proto::eval() that explodes each node and calls the derived context
    /// type with the expressions constituents. If the derived context doesn't
    /// have an overload that handles this node, fall-back to the default_context.
    /// TODO: make the fall-back configurable!
    //
    //  Copyright 2004 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_CONTEXT_CALLABLE_HPP_EAN_06_23_2007
    #define BOOST_PROTO_CONTEXT_CALLABLE_HPP_EAN_06_23_2007

    #include <boost/xpressive/proto/detail/prefix.hpp> // must be first include
    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/selection/max.hpp>
    #include <boost/mpl/bool.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/type_traits/remove_cv.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/tags.hpp>
    #include <boost/xpressive/proto/eval.hpp>
    #include <boost/xpressive/proto/context/default.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp> // must be last include

    namespace boost { namespace proto
    {

        template<typename Expr, typename Context, long Arity = Expr::proto_arity::value>
        struct callable_eval
        {};

        namespace detail
        {
            struct dont_care
            {
                dont_care(...);
            };
        }

    #define BOOST_PROTO_ARG_N_TYPE(Z, N, Expr)                                                      \
        typename proto::result_of::arg_c<Expr, N>::const_reference                                  \
        /**/

    #define BOOST_PROTO_ARG_N(Z, N, expr)                                                           \
        proto::arg_c<N>(expr)                                                                       \
        /**/

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/context/callable.hpp>))               \
        /**/

    #include BOOST_PP_ITERATE()

    #undef BOOST_PROTO_ARG_N_TYPE
    #undef BOOST_PROTO_ARG_N

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
    #define ARG_COUNT BOOST_PP_MAX(1, N)

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
                struct private_type_ { private_type_ const &operator,(int) const; };
                typedef private_type_ const &(*pointer_to_function)(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(ARG_COUNT), detail::dont_care BOOST_PP_INTERCEPT));
                operator pointer_to_function() const;
            };

        public:
            typedef
                typename boost::result_of<
                    Context(
                        typename Expr::proto_tag
                        BOOST_PP_ENUM_TRAILING(ARG_COUNT, BOOST_PROTO_ARG_N_TYPE, Expr)
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
                                    typename Expr::proto_tag()
                                    BOOST_PP_ENUM_TRAILING(ARG_COUNT, BOOST_PROTO_ARG_N, expr)
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
                    typename Expr::proto_tag()
                    BOOST_PP_ENUM_TRAILING(ARG_COUNT, BOOST_PROTO_ARG_N, expr)
                );
            }

            result_type operator ()(Expr &expr, Context &context, mpl::false_) const
            {
                return default_eval<Expr, Context>()(expr, context);
            }
        };

    #undef N
    #undef ARG_COUNT

#endif
