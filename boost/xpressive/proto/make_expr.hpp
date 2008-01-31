#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr.hpp
    /// Definition of the \c make_expr() and \c unpack_expr() utilities for
    /// building Proto expression nodes from children nodes or from a Fusion
    /// sequence of children nodes, respectively.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005
    #define BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

    #include <boost/xpressive/proto/detail/prefix.hpp>
    #include <boost/version.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/control/if.hpp>
    #include <boost/preprocessor/control/expr_if.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/comparison/greater.hpp>
    #include <boost/preprocessor/tuple/elem.hpp>
    #include <boost/preprocessor/tuple/to_list.hpp>
    #include <boost/preprocessor/logical/and.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/repeat_from_to.hpp>
    #include <boost/preprocessor/seq/size.hpp>
    #include <boost/preprocessor/seq/enum.hpp>
    #include <boost/preprocessor/seq/seq.hpp>
    #include <boost/preprocessor/seq/to_tuple.hpp>
    #include <boost/preprocessor/seq/for_each_i.hpp>
    #include <boost/preprocessor/seq/pop_back.hpp>
    #include <boost/preprocessor/seq/push_back.hpp>
    #include <boost/preprocessor/seq/push_front.hpp>
    #include <boost/preprocessor/list/for_each_i.hpp>
    #include <boost/ref.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/apply_wrap.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/type_traits/is_same.hpp>
    #include <boost/type_traits/add_const.hpp>
    #include <boost/type_traits/add_reference.hpp>
    #include <boost/type_traits/remove_reference.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/domain.hpp>
    #include <boost/xpressive/proto/generate.hpp>
    #if BOOST_VERSION >= 103500
    # include <boost/fusion/include/at.hpp>
    # include <boost/fusion/include/value_at.hpp>
    # include <boost/fusion/include/size.hpp>
    #else
    # include <boost/spirit/fusion/sequence/at.hpp>
    # include <boost/spirit/fusion/sequence/value_at.hpp>
    # include <boost/spirit/fusion/sequence/size.hpp>
    #endif
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost
    {
        /// INTERNAL ONLY
        ///
        namespace fusion
        {
            /// INTERNAL ONLY
            ///
            template<typename Function>
            class unfused_generic;
        }
    }

    namespace boost { namespace proto
    {
    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_AS_ARG_TYPE(Z, N, DATA)                                                     \
        typename boost::proto::detail::protoify_<                                                   \
            BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, DATA), N)                                        \
          , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
        >::type                                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_AS_ARG(Z, N, DATA)                                                          \
        boost::proto::detail::protoify_<                                                            \
            BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 0, DATA), N)                                        \
          , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
        >::call(BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(3, 1, DATA), N))                                   \
        /**/

    /// INTERNAL ONLY
    ///
    # define BOOST_PROTO_AT_TYPE(Z, N, DATA)                                                        \
        typename add_const<                                                                         \
            typename fusion::BOOST_PROTO_FUSION_RESULT_OF::value_at_c<                              \
                BOOST_PP_TUPLE_ELEM(3, 0, DATA)                                                     \
              , N                                                                                   \
            >::type                                                                                 \
        >::type                                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    # define BOOST_PROTO_AT(Z, N, DATA)                                                             \
        fusion::BOOST_PROTO_FUSION_AT_C(N, BOOST_PP_TUPLE_ELEM(3, 1, DATA))                         \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_AS_ARG_AT_TYPE(Z, N, DATA)                                                  \
        typename boost::proto::detail::protoify_<                                                   \
            BOOST_PROTO_AT_TYPE(Z, N, DATA)                                                         \
          , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
        >::type                                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_AS_ARG_AT(Z, N, DATA)                                                       \
        boost::proto::detail::protoify_<                                                            \
            BOOST_PROTO_AT_TYPE(Z, N, DATA)                                                         \
          , BOOST_PP_TUPLE_ELEM(3, 2, DATA)                                                         \
        >::call(BOOST_PROTO_AT(Z, N, DATA))                                                         \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TEMPLATE_AUX_(R, DATA, I, ELEM)                                      \
        (ELEM BOOST_PP_CAT(BOOST_PP_CAT(X, DATA), BOOST_PP_CAT(_, I)))                              \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TEMPLATE_YES_(R, DATA, I, ELEM)                                      \
        BOOST_PP_LIST_FOR_EACH_I_R(                                                                 \
            R                                                                                       \
          , BOOST_PROTO_VARARG_TEMPLATE_AUX_                                                        \
          , I                                                                                       \
          , BOOST_PP_TUPLE_TO_LIST(                                                                 \
                BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                               \
              , BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_TAIL(ELEM))                                      \
            )                                                                                       \
        )                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TEMPLATE_NO_(R, DATA, I, ELEM)                                       \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TEMPLATE_(R, DATA, I, ELEM)                                          \
        BOOST_PP_IF(                                                                                \
            BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                                   \
          , BOOST_PROTO_VARARG_TEMPLATE_YES_                                                        \
          , BOOST_PROTO_VARARG_TEMPLATE_NO_                                                         \
        )(R, DATA, I, ELEM)                                                                         \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TYPE_AUX_(R, DATA, I, ELEM)                                          \
        (BOOST_PP_CAT(BOOST_PP_CAT(X, DATA), BOOST_PP_CAT(_, I)))                                   \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_PARAMS_YES_(R, DATA, I, ELEM)                                      \
        <                                                                                           \
            BOOST_PP_SEQ_ENUM(                                                                      \
                BOOST_PP_LIST_FOR_EACH_I_R(                                                         \
                    R                                                                               \
                  , BOOST_PROTO_VARARG_TYPE_AUX_                                                    \
                  , I                                                                               \
                  , BOOST_PP_TUPLE_TO_LIST(                                                         \
                        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                       \
                      , BOOST_PP_SEQ_TO_TUPLE(BOOST_PP_SEQ_TAIL(ELEM))                              \
                    )                                                                               \
                )                                                                                   \
            )                                                                                       \
        >                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_TEMPLATE_PARAMS_NO_(R, DATA, I, ELEM)                                       \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_TYPE_(R, DATA, I, ELEM)                                              \
        BOOST_PP_COMMA_IF(I)                                                                        \
        BOOST_PP_SEQ_HEAD(ELEM)                                                                     \
        BOOST_PP_IF(                                                                                \
            BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                                   \
          , BOOST_PROTO_TEMPLATE_PARAMS_YES_                                                        \
          , BOOST_PROTO_TEMPLATE_PARAMS_NO_                                                         \
        )(R, DATA, I, ELEM) BOOST_PP_EXPR_IF(BOOST_PP_GREATER(I, 1), const)                         \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_AS_EXPR_(R, DATA, I, ELEM)                                           \
        BOOST_PP_EXPR_IF(                                                                           \
            BOOST_PP_GREATER(I, 1)                                                                  \
          , ((                                                                                      \
                BOOST_PP_SEQ_HEAD(ELEM)                                                             \
                BOOST_PP_IF(                                                                        \
                    BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(ELEM))                                           \
                  , BOOST_PROTO_TEMPLATE_PARAMS_YES_                                                \
                  , BOOST_PROTO_TEMPLATE_PARAMS_NO_                                                 \
                )(R, DATA, I, ELEM)()                                                               \
            ))                                                                                      \
        )                                                                                           \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_AS_ARG_(Z, N, DATA)                                                  \
        (BOOST_PP_CAT(DATA, N))                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_SEQ_PUSH_FRONT(SEQ, ELEM)                                                   \
        BOOST_PP_SEQ_POP_BACK(BOOST_PP_SEQ_PUSH_FRONT(BOOST_PP_SEQ_PUSH_BACK(SEQ, _dummy_), ELEM))  \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_AS_PARAM_(Z, N, DATA)                                                \
        (BOOST_PP_CAT(DATA, N))                                                                     \
        /**/

    /// INTERNAL ONLY
    ///
    #define BOOST_PROTO_VARARG_FUN_(Z, N, DATA)                                                     \
        template<                                                                                   \
            BOOST_PP_SEQ_ENUM(                                                                      \
                BOOST_PP_SEQ_FOR_EACH_I(                                                            \
                    BOOST_PROTO_VARARG_TEMPLATE_, ~                                                 \
                  , BOOST_PP_SEQ_PUSH_FRONT(                                                        \
                        BOOST_PROTO_SEQ_PUSH_FRONT(                                                 \
                            BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                         \
                          , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                       \
                        )                                                                           \
                      , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                             \
                    )                                                                               \
                )                                                                                   \
                BOOST_PP_REPEAT_ ## Z(N, BOOST_PROTO_VARARG_AS_PARAM_, typename A)                  \
            )                                                                                       \
        >                                                                                           \
        typename boost::proto::result_of::make_expr<                                                \
            BOOST_PP_SEQ_FOR_EACH_I(                                                                \
                BOOST_PROTO_VARARG_TYPE_, ~                                                         \
              , BOOST_PP_SEQ_PUSH_FRONT(                                                            \
                    BOOST_PROTO_SEQ_PUSH_FRONT(                                                     \
                        BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                             \
                      , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                           \
                    )                                                                               \
                  , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                                 \
                )                                                                                   \
            )                                                                                       \
            BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(Z, N, A, const & BOOST_PP_INTERCEPT)             \
        >::type const                                                                               \
        BOOST_PP_TUPLE_ELEM(4, 0, DATA)(BOOST_PP_ENUM_BINARY_PARAMS_Z(Z, N, A, const &a))           \
        {                                                                                           \
            return boost::proto::detail::make_expr_<                                                \
                BOOST_PP_SEQ_FOR_EACH_I(                                                            \
                    BOOST_PROTO_VARARG_TYPE_, ~                                                     \
                  , BOOST_PP_SEQ_PUSH_FRONT(                                                        \
                        BOOST_PROTO_SEQ_PUSH_FRONT(                                                 \
                            BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                         \
                          , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                       \
                        )                                                                           \
                      , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                             \
                    )                                                                               \
                )                                                                                   \
                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(Z, N, A, const & BOOST_PP_INTERCEPT)         \
            >::call(                                                                                \
                BOOST_PP_SEQ_ENUM(                                                                  \
                    BOOST_PP_SEQ_FOR_EACH_I(                                                        \
                        BOOST_PROTO_VARARG_AS_EXPR_, ~                                              \
                      , BOOST_PP_SEQ_PUSH_FRONT(                                                    \
                            BOOST_PROTO_SEQ_PUSH_FRONT(                                             \
                                BOOST_PP_TUPLE_ELEM(4, 2, DATA)                                     \
                              , (BOOST_PP_TUPLE_ELEM(4, 3, DATA))                                   \
                            )                                                                       \
                          , BOOST_PP_TUPLE_ELEM(4, 1, DATA)                                         \
                        )                                                                           \
                    )                                                                               \
                    BOOST_PP_REPEAT_ ## Z(N, BOOST_PROTO_VARARG_AS_ARG_, a)                         \
                )                                                                                   \
            );                                                                                      \
        }                                                                                           \
        /**/

    /// \code
    /// BOOST_PROTO_DEFINE_FUNCTION_TEMPLATE(
    ///     1
    ///   , construct
    ///   , boost::proto::default_domain
    ///   , (boost::proto::tag::function)
    ///   , ((op::construct)(typename)(int))
    /// )
    /// \endcode
    #define BOOST_PROTO_DEFINE_FUNCTION_TEMPLATE(ARGCOUNT, NAME, DOMAIN, TAG, BOUNDARGS)            \
        BOOST_PP_REPEAT_FROM_TO(                                                                    \
            ARGCOUNT                                                                                \
          , BOOST_PP_INC(ARGCOUNT)                                                                  \
          , BOOST_PROTO_VARARG_FUN_                                                                 \
          , (NAME, TAG, BOUNDARGS, DOMAIN)                                                          \
        )\
        /**/

    /// \code
    /// BOOST_PROTO_DEFINE_VARARG_FUNCTION_TEMPLATE(
    ///     construct
    ///   , boost::proto::default_domain
    ///   , (boost::proto::tag::function)
    ///   , ((op::construct)(typename)(int))
    /// )
    /// \endcode
    #define BOOST_PROTO_DEFINE_VARARG_FUNCTION_TEMPLATE(NAME, DOMAIN, TAG, BOUNDARGS)               \
        BOOST_PP_REPEAT(                                                                            \
            BOOST_PP_SUB(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), BOOST_PP_SEQ_SIZE(BOUNDARGS))         \
          , BOOST_PROTO_VARARG_FUN_                                                                 \
          , (NAME, TAG, BOUNDARGS, DOMAIN)                                                          \
        )                                                                                           \
        /**/

        namespace detail
        {
            template<typename T, typename Domain>
            struct protoify_
            {
                typedef
                    typename mpl::eval_if<
                        boost::is_reference_wrapper<T>
                      , proto::result_of::as_arg<typename boost::unwrap_reference<T>::type, Domain>
                      , proto::result_of::as_expr<T, Domain>
                    >::type
                type;

                static type call(T &t)
                {
                    return typename mpl::if_<
                        is_reference_wrapper<T>
                      , functional::as_arg<Domain>
                      , functional::as_expr<Domain>
                    >::type()(static_cast<typename boost::unwrap_reference<T>::type &>(t));
                }
            };

            template<typename T, typename Domain>
            struct protoify_<T &, Domain>
            {
                typedef
                    typename proto::result_of::as_arg<
                        typename boost::unwrap_reference<T>::type
                      , Domain
                    >::type
                type;

                static type call(T &t)
                {
                    return functional::as_arg<Domain>()(
                        static_cast<typename boost::unwrap_reference<T>::type &>(t)
                    );
                }
            };

            template<
                typename Domain
                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
                    BOOST_PROTO_MAX_ARITY
                  , typename A
                  , = default_domain BOOST_PP_INTERCEPT
                )
            >
            struct deduce_domain_
            {
                typedef Domain type;
            };

            template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)>
            struct deduce_domain_<
                default_domain
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
            >
              : deduce_domain_<
                    typename domain_of<A0>::type
                  , BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                >
            {};

            template<>
            struct deduce_domain_<default_domain>
            {
                typedef default_domain type;
            };

            template<typename Tag, typename Domain, typename Sequence, std::size_t Size>
            struct unpack_expr_
            {};

            template<typename Domain, typename Sequence>
            struct unpack_expr_<tag::terminal, Domain, Sequence, 1u>
            {
                typedef
                    typename add_const<
                        typename fusion::BOOST_PROTO_FUSION_RESULT_OF::value_at_c<
                            Sequence
                          , 0
                        >::type
                    >::type
                terminal_type;

                typedef
                    typename proto::detail::protoify_<
                        terminal_type
                      , Domain
                    >::type
                type;

                static type const call(Sequence const &sequence)
                {
                    return proto::detail::protoify_<terminal_type, Domain>::call(fusion::BOOST_PROTO_FUSION_AT_C(0, sequence));
                }
            };

            template<typename Sequence>
            struct unpack_expr_<tag::terminal, deduce_domain, Sequence, 1u>
              : unpack_expr_<tag::terminal, default_domain, Sequence, 1u>
            {};

            template<
                typename Tag
              , typename Domain
                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
                    BOOST_PROTO_MAX_ARITY
                  , typename A
                  , = void BOOST_PP_INTERCEPT
                )
              , typename _ = void
            >
            struct make_expr_
            {};

            template<typename Domain, typename A>
            struct make_expr_<tag::terminal, Domain, A
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
            {
                typedef typename proto::detail::protoify_<A, Domain>::type type;

                static type const call(typename add_reference<A>::type a)
                {
                    return proto::detail::protoify_<A, Domain>::call(a);
                }
            };

            template<typename A>
            struct make_expr_<tag::terminal, deduce_domain, A
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, void BOOST_PP_INTERCEPT)>
              : make_expr_<tag::terminal, default_domain, A>
            {};

        #define BOOST_PP_ITERATION_PARAMS_1                                                         \
            (4, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/make_expr.hpp>, 1))               \
            /**/

        #include BOOST_PP_ITERATE()
        }

        namespace result_of
        {
            template<typename Tag, typename Sequence, typename EnableIf1, typename EnableIf2>
            struct unpack_expr
            {
                typedef
                    typename detail::unpack_expr_<
                        Tag
                      , deduce_domain
                      , Sequence
                      , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence>::type::value
                    >::type
                type;
            };

            template<typename Tag, typename Domain, typename Sequence>
            struct unpack_expr<Tag, Domain, Sequence, typename Domain::proto_is_domain_>
            {
                typedef
                    typename detail::unpack_expr_<
                        Tag
                      , Domain
                      , Sequence
                      , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence>::type::value
                    >::type
                type;
            };

            template<
                typename Tag
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)
              , typename EnableIf1
              , typename EnableIf2
            >
            struct make_expr
            {
                typedef
                    typename detail::make_expr_<
                        Tag
                      , deduce_domain
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                    >::type
                type;
            };

            template<
                typename Tag
              , typename Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, typename A)
            >
            struct make_expr<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
              , typename Domain::proto_is_domain_
            >
            {
                typedef
                    typename detail::make_expr_<
                        Tag
                      , Domain
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, A)
                    >::type
                type;
            };
        }

        namespace functional
        {
            template<typename Tag, typename Domain>
            struct make_expr
            {
                BOOST_PROTO_CALLABLE()

                template<typename Sig>
                struct result {};

                template<typename This, typename A0>
                struct result<This(A0)>
                {
                    typedef
                        typename result_of::make_expr<
                            Tag
                          , Domain
                          , A0
                        >::type
                    type;
                };

                /// Construct an expression node with tag type \c Tag
                /// and in the domain \c Domain.
                template<typename A0>
                typename result_of::make_expr<
                    Tag
                  , Domain
                  , A0 const
                >::type const
                operator ()(A0 const &a0) const
                {
                    return proto::detail::make_expr_<
                        Tag
                      , Domain
                      , A0 const
                    >::call(a0);
                }

                // Additional overloads generated by the preprocessor ...

            #define BOOST_PP_ITERATION_PARAMS_1                                                         \
                (4, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/make_expr.hpp>, 2))               \
                /**/

            #include BOOST_PP_ITERATE()
            };

            template<typename Tag, typename Domain>
            struct unpack_expr
            {
                BOOST_PROTO_CALLABLE()

                template<typename Sig>
                struct result
                {};

                template<typename This, typename Sequence>
                struct result<This(Sequence)>
                {
                    typedef
                        typename result_of::unpack_expr<
                            Tag
                          , Domain
                          , typename remove_reference<Sequence>::type
                        >::type
                    type;
                };

                template<typename Sequence>
                typename result_of::unpack_expr<Tag, Domain, Sequence const>::type const
                operator ()(Sequence const &sequence) const
                {
                    return proto::detail::unpack_expr_<
                        Tag
                      , Domain
                      , Sequence const
                      , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence>::type::value
                    >::call(sequence);
                }
            };

            /// INTERNAL ONLY
            ///
            template<typename Tag, typename Domain>
            struct unfused_expr_fun
            {
                BOOST_PROTO_CALLABLE()

                template<typename Sig>
                struct result {};

                template<typename This, typename Sequence>
                struct result<This(Sequence)>
                {
                    typedef
                        typename result_of::unpack_expr<
                            Tag
                          , Domain
                          , typename remove_reference<Sequence>::type
                        >::type
                    type;
                };

                template<typename Sequence>
                typename proto::result_of::unpack_expr<Tag, Domain, Sequence const>::type const
                operator ()(Sequence const &sequence) const
                {
                    return proto::detail::unpack_expr_<
                        Tag
                      , Domain
                      , Sequence const
                      , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence>::type::value
                    >::call(sequence);
                }
            };

            /// INTERNAL ONLY
            ///
            template<typename Tag, typename Domain>
            struct unfused_expr
              : fusion::unfused_generic<unfused_expr_fun<Tag, Domain> >
            {
                BOOST_PROTO_CALLABLE()
            };
        }

        /// unpack_expr
        ///
        template<typename Tag, typename Sequence>
        typename lazy_disable_if<
            is_domain<Sequence>
          , result_of::unpack_expr<Tag, Sequence const>
        >::type const
        unpack_expr(Sequence const &sequence)
        {
            return proto::detail::unpack_expr_<
                Tag
              , deduce_domain
              , Sequence const
              , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence>::type::value
            >::call(sequence);
        }

        /// \overload
        ///
        template<typename Tag, typename Domain, typename Sequence2>
        typename result_of::unpack_expr<Tag, Domain, Sequence2 const>::type const
        unpack_expr(Sequence2 const &sequence2)
        {
            return proto::detail::unpack_expr_<
                Tag
              , Domain
              , Sequence2 const
              , fusion::BOOST_PROTO_FUSION_RESULT_OF::size<Sequence2>::type::value
            >::call(sequence2);
        }

        /// make_expr
        ///
        template<typename Tag, typename A0>
        typename lazy_disable_if<
            is_domain<A0>
          , result_of::make_expr<
                Tag
              , A0 const
            >
        >::type const
        make_expr(A0 const &a0)
        {
            return proto::detail::make_expr_<
                Tag
              , deduce_domain 
              , A0 const
            >::call(a0);
        }

        /// \overload
        ///
        template<typename Tag, typename Domain, typename B0>
        typename result_of::make_expr<
            Tag
          , Domain
          , B0 const
        >::type const
        make_expr(B0 const &b0)
        {
            return proto::detail::make_expr_<
                Tag
              , Domain
              , B0 const
            >::call(b0);
        }

        // Additional overloads generated by the preprocessor...

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (4, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/make_expr.hpp>, 3))                   \
        /**/

    #include BOOST_PP_ITERATE()

        template<typename Tag, typename Domain>
        struct is_callable<functional::make_expr<Tag, Domain> >
          : mpl::true_
        {};

        template<typename Tag, typename Domain>
        struct is_callable<functional::unpack_expr<Tag, Domain> >
          : mpl::true_
        {};

        /// INTERNAL ONLY
        ///
        template<typename Tag, typename Domain>
        struct is_callable<functional::unfused_expr<Tag, Domain> >
          : mpl::true_
        {};

    }}

    #undef BOOST_PROTO_AT
    #undef BOOST_PROTO_AT_TYPE
    #undef BOOST_PROTO_AS_ARG_AT
    #undef BOOST_PROTO_AS_ARG_AT_TYPE

    #endif // BOOST_PROTO_MAKE_EXPR_HPP_EAN_04_01_2005

#elif BOOST_PP_ITERATION_FLAGS() == 1

    #define N BOOST_PP_ITERATION()
    #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)

        template<typename Tag, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct make_expr_<Tag, Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
        {
            typedef proto::expr<
                Tag
              , BOOST_PP_CAT(args, N)<BOOST_PP_ENUM(N, BOOST_PROTO_AS_ARG_TYPE, (A, ~, Domain)) >
            > expr_type;

            typedef typename Domain::template apply<expr_type>::type type;

            static type const call(BOOST_PP_ENUM_BINARY_PARAMS(N, typename add_reference<A, >::type a))
            {
                expr_type that = {
                    BOOST_PP_ENUM(N, BOOST_PROTO_AS_ARG, (A, a, Domain))
                };
                return Domain::make(that);
            }
        };

        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct make_expr_<Tag, deduce_domain BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            BOOST_PP_ENUM_TRAILING_PARAMS(M, void BOOST_PP_INTERCEPT), void>
          : make_expr_<
                Tag
              , typename detail::deduce_domain_<
                    typename domain_of<
                        A0
                    >::type
                    BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                    BOOST_PP_ENUM_SHIFTED_PARAMS(N, A)
                >::type
                BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
            >
        {};

        template<typename Tag, typename Domain, typename Sequence>
        struct unpack_expr_<Tag, Domain, Sequence, N>
        {
            typedef proto::expr<
                Tag
              , BOOST_PP_CAT(args, N)<
                    BOOST_PP_ENUM(N, BOOST_PROTO_AS_ARG_AT_TYPE, (Sequence const, ~, Domain))
                >
            > expr_type;

            typedef typename Domain::template apply<expr_type>::type type;

            static type const call(Sequence const &sequence)
            {
                expr_type that = {
                    BOOST_PP_ENUM(N, BOOST_PROTO_AS_ARG_AT, (Sequence const, sequence, Domain))
                };
                return Domain::make(that);
            }
        };

        template<typename Tag, typename Sequence>
        struct unpack_expr_<Tag, deduce_domain, Sequence, N>
          : unpack_expr_<
                Tag
              , typename detail::deduce_domain_<
                    typename domain_of<
                        BOOST_PROTO_AT_TYPE(~, 0, (Sequence const, ~, ~))
                    >::type
                    BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_AT_TYPE, (Sequence const, ~, ~))
                >::type
              , Sequence
              , N
            >
        {};

    #undef N
    #undef M

#elif BOOST_PP_ITERATION_FLAGS() == 2

    #define N BOOST_PP_ITERATION()

        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef
                typename result_of::make_expr<
                    Tag
                  , Domain
                    BOOST_PP_ENUM_TRAILING_PARAMS(N, A)
                >::type
            type;
        };

        /// \overload
        ///
        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        typename result_of::make_expr<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
        >::type const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a)) const
        {
            return proto::detail::make_expr_<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(BOOST_PP_ENUM_PARAMS(N, a));
        }

    #undef N

#elif BOOST_PP_ITERATION_FLAGS() == 3

    #define N BOOST_PP_ITERATION()

        /// \overload
        ///
        template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        typename lazy_disable_if<
            is_domain<A0>
          , result_of::make_expr<
                Tag
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >
        >::type const
        make_expr(BOOST_PP_ENUM_BINARY_PARAMS(N, const A, &a))
        {
            return proto::detail::make_expr_<
                Tag
              , deduce_domain 
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const A)
            >::call(BOOST_PP_ENUM_PARAMS(N, a));
        }

        /// \overload
        ///
        template<typename Tag, typename Domain BOOST_PP_ENUM_TRAILING_PARAMS(N, typename B)>
        typename result_of::make_expr<
            Tag
          , Domain
            BOOST_PP_ENUM_TRAILING_PARAMS(N, const B)
        >::type const
        make_expr(BOOST_PP_ENUM_BINARY_PARAMS(N, const B, &b))
        {
            return proto::detail::make_expr_<
                Tag
              , Domain
                BOOST_PP_ENUM_TRAILING_PARAMS(N, const B)
            >::call(BOOST_PP_ENUM_PARAMS(N, b));
        }

    #undef N

#endif // BOOST_PP_IS_ITERATING
