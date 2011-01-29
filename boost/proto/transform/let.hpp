#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file let.hpp
    /// Contains definition of the let transform.
    //
    //  Copyright 2010 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_TRANSFORM_LET_HPP_EAN_12_04_2010
    #define BOOST_PROTO_TRANSFORM_LET_HPP_EAN_12_04_2010

    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/arithmetic/inc.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/eval_if.hpp>
    #include <boost/mpl/identity.hpp>
    #include <boost/mpl/aux_/template_arity.hpp>
    #include <boost/mpl/aux_/lambda_arity_param.hpp>
    #include <boost/fusion/include/map.hpp>
    #include <boost/fusion/include/at_key.hpp>
    #include <boost/proto/proto_fwd.hpp>
    #include <boost/proto/traits.hpp>
    #include <boost/proto/transform/impl.hpp>

    namespace boost { namespace proto
    {
        template<typename T>
        struct is_let
          : mpl::false_
        {};

        template<BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), typename T)>
        struct is_let<let<BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(BOOST_PROTO_MAX_ARITY), T)> >
          : mpl::true_
        {};

        namespace detail
        {
            // A structure that holds both a map of local variables as
            // well as the original Data parameter passed to the let transform
            template<typename LocalMap, typename Data>
            struct let_scope
            {
                LocalMap locals;
                Data data;

                typedef Data data_type;

                data_type get_data()
                {
                    return data;
                }

                template<typename Key>
                struct at_key
                  : fusion::result_of::at_key<LocalMap, Key>
                {};

                template<typename Key>
                typename fusion::result_of::at_key<LocalMap, Key>::type
                get_local()
                {
                    return fusion::at_key<Key>(locals);
                }
            };

            // Specialization to handle an outer let scope that holds a
            // reference to an inner let scope.
            template<typename LocalMap, typename OtherMap, typename Data>
            struct let_scope<LocalMap, let_scope<OtherMap, Data> &>
            {
                LocalMap locals;
                let_scope<OtherMap, Data> &data;

                typedef typename let_scope<OtherMap, Data>::data_type data_type;

                data_type get_data()
                {
                    return data.get_data();
                }

                template<typename Key>
                struct at_key
                  : mpl::eval_if_c<
                        fusion::result_of::has_key<LocalMap, Key>::value
                      , fusion::result_of::at_key<LocalMap, Key>
                      , typename let_scope<OtherMap, Data>::template at_key<Key>
                    >
                {};

                template<typename Key>
                typename at_key<Key>::type get_local()
                {
                    return this->get_local_impl<Key>(fusion::result_of::has_key<LocalMap, Key>());
                }

            private:
                template<typename Key>
                typename at_key<Key>::type get_local_impl(mpl::true_)
                {
                    return fusion::at_key<Key>(locals);
                }

                template<typename Key>
                typename at_key<Key>::type get_local_impl(mpl::false_)
                {
                    return data.get_local<Key>();
                }
            };

            template<typename Expr, typename State, typename Data
                BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(BOOST_PROTO_MAX_ARITY, typename Local, = void BOOST_PP_INTERCEPT)
              , typename Transform = void
            >
            struct init_local_map;

            // A transnform that fetches the original data parameter out of a let_scope
            struct _get_data : transform<_get_data>
            {
                template<typename Expr, typename State, typename Data>
                struct impl;

                template<typename Expr, typename State, typename LocalMap, typename Data>
                struct impl<Expr, State, let_scope<LocalMap, Data> &>
                  : transform_impl<Expr, State, let_scope<LocalMap, Data> &>
                {
                    typedef typename let_scope<LocalMap, Data>::data_type result_type;

                    result_type operator()(
                        typename impl::expr_param
                      , typename impl::state_param
                      , typename impl::data_param d
                    ) const
                    {
                        return d.get_data();
                    }
                };
            };

            template<typename T>
            struct rewrite_transform;

            template<typename T>
            struct rewrite_args
            {
                typedef T type;
            };

            // rewrite_object if T is not a template....
            template<
                typename T
                BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(long Arity = mpl::aux::template_arity<T>::value)
            >
            struct rewrite_object
              : mpl::eval_if_c<
                    is_transform<T>::value
                  , rewrite_transform<T>
                  , mpl::identity<T>
                >
            {};

            // rewrite_makeable if Object is not a function type (or pointer to function type)
            template<typename Object>
            struct rewrite_makeable
            {
                typedef proto::make<typename rewrite_object<Object>::type> type;
            };

            // rewrite_callable if T is a PrimitiveTransform or a function of arity >2
            template<typename T>
            struct rewrite_callable
            {
                typedef proto::call<T> type;
            };

            template<typename Sig>
            struct rewrite_callable<Sig *>
              : rewrite_callable<Sig>
            {};

            template<typename R>
            struct rewrite_callable<R()>
              : mpl::if_c<
                    is_transform<R>::value && !is_let<R>::value
                  , proto::call<R(_, _state, _get_data)>
                  , proto::call<R()>
                >
            {};

            template<typename R, typename A0>
            struct rewrite_callable<R(A0)>
              : mpl::if_c<
                    is_transform<R>::value && !is_let<R>::value
                  , proto::call<R(A0, _state, _get_data)>
                  , proto::call<R(A0)>
                >
            {};

            template<typename R, typename A0, typename A1>
            struct rewrite_callable<R(A0, A1)>
              : mpl::if_c<
                    is_transform<R>::value && !is_let<R>::value
                  , proto::call<R(A0, A1, _get_data)>
                  , proto::call<R(A0, A1)>
                >
            {};

            // rewrite_lazyable if Object is not a function type (or pointer to function type)
            template<typename Object>
            struct rewrite_lazyable
            {
                typedef proto::lazy<typename rewrite_object<Object>::type> type;
            };

            // Why all the complexity and special handling for certain Proto transforms?
            // Note: make<> is a transform, but we don't want to monkey with the data parameter yet
            //
            //    let<_a, make<foo<_a> > >          => make<foo<_a> >
            //    let<_a, make<foo<_a>(_data)> >    => make<foo<_a>(call<_data(_, _state, _get_data))> >
            //
            // Here, we do want to monkey with the data parameter, so just checking if T<X> is a
            // transform is insufficient.
            //
            //    let<_a, MyTransform<X> >          => call<MyTransform<X>(_, _state, _get_data)>

            template<typename T>
            struct rewrite_transform
              : mpl::if_c<
                     is_let<T>::value
                   , T
                   , proto::call<T(_, _state, _get_data)>
                >
            {};

        #define BOOST_PROTO_IGNORE_ARITY(I)

            // Some Proto transforms need to be handled specially by the let rewritter rules
        #define BOOST_PROTO_HANDLE_SPECIAL_TRANSFORMS(X, ARITY)                                     \
            template<typename T>                                                                    \
            struct X<proto::call<T> ARITY(1)>                                                       \
              : rewrite_callable<typename rewrite_args<T>::type>                                    \
            {};                                                                                     \
                                                                                                    \
            template<typename T>                                                                    \
            struct X<proto::make<T> ARITY(1)>                                                       \
              : rewrite_makeable<typename rewrite_args<T>::type>                                    \
            {};                                                                                     \
                                                                                                    \
            template<typename T>                                                                    \
            struct X<proto::lazy<T> ARITY(1)>                                                       \
              : rewrite_lazyable<typename rewrite_args<T>::type>                                    \
            {};                                                                                     \
                                                                                                    \
            template<typename Tag>                                                                  \
            struct X<local<Tag> ARITY(1)>                                                           \
            {                                                                                       \
                typedef local<Tag> type;                                                            \
            };                                                                                      \
            /**/

            // These must be kept in sync, hence the macros.
            BOOST_PROTO_HANDLE_SPECIAL_TRANSFORMS(rewrite_transform, BOOST_PROTO_IGNORE_ARITY)
            BOOST_PROTO_HANDLE_SPECIAL_TRANSFORMS(rewrite_object, BOOST_MPL_AUX_LAMBDA_ARITY_PARAM)

            #undef BOOST_PROTO_IGNORE_ARITY
            #undef BOOST_PROTO_HANDLE_SPECIAL_TRANSFORMS

            #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/let.hpp>))
            #include BOOST_PP_ITERATE()
        }

        template<typename Tag>
        struct local : transform<local<Tag> >
        {
            // TODO put something here to give a sensible compile error 
            // when a local variable is used out of a let scope.
            template<typename Expr, typename State, typename Data>
            struct impl;

            template<typename Expr, typename State, typename LocalMap, typename Data>
            struct impl<Expr, State, detail::let_scope<LocalMap, Data> &>
              : transform_impl<Expr, State, detail::let_scope<LocalMap, Data> &>
            {
                typedef
                    typename detail::let_scope<LocalMap, Data>::template at_key<local<Tag> >::type
                result_type;

                result_type operator()(
                    typename impl::expr_param
                  , typename impl::state_param
                  , typename impl::data_param d
                ) const
                {
                    return d.template get_local<local<Tag> >();
                }
            };
        };

        /// \brief A PrimitiveTransform that allows the result of one
        /// computation to be saved off before invoking another transform
        ///
        /// Example:
        ///
        /// \code
        /// struct RenumberFun
        ///   : proto::fold<
        ///         _
        ///       , make_pair(fusion::vector0<>(), proto::_state)
        ///       , let<
        ///             _a(Renumber(_, second(proto::_state)))
        ///           , make_pair(
        ///                 push_back(first(proto::_state), first(_a))
        ///               , second(_a)
        ///             )
        ///         >
        ///     >
        /// {};
        /// \endcode
        template<
            BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename Local)
          , typename Transform
        >
        struct let
          : transform<let<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, Local), Transform> >
        {
            template<typename Expr, typename State, typename Data>
            struct impl : transform_impl<Expr, State, Data>
            {
                typedef
                    detail::init_local_map<
                        Expr, State, Data
                        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PROTO_MAX_ARITY, Local)
                      , Transform
                    >
                init_local_map;
                typedef typename init_local_map::transform_type transform_type;
                typedef typename init_local_map::local_map_type local_map_type;
                typedef detail::let_scope<local_map_type, Data> let_scope;
                typedef typename transform_type::template impl<Expr, State, let_scope &>::result_type result_type;

                result_type operator()(
                    typename impl::expr_param e
                  , typename impl::state_param s
                  , typename impl::data_param d
                ) const
                {
                    let_scope scope = {init_local_map::call(e, s, d), d};
                    return typename transform_type::template impl<Expr, State, let_scope &>()(e, s, scope);
                }
            };
        };

        /// INTERNAL ONLY
        ///
        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename Local), typename Transform>
        struct is_callable<let<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, Local), Transform> >
          : mpl::true_
        {};

        /// INTERNAL ONLY
        ///
        template<typename Tag>
        struct is_callable<local<Tag> >
          : mpl::true_
        {};

  }}

  #endif

#else

    #define N BOOST_PP_ITERATION()

        // rewrite_args
        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct rewrite_args<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef R type(BOOST_PP_ENUM_BINARY_PARAMS(N, typename rewrite_transform<A, >::type BOOST_PP_INTERCEPT));
        };

        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct rewrite_args<R(*)(BOOST_PP_ENUM_PARAMS(N, A))>
          : rewrite_args<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

        #if N > 0
        // rewrite_object
        template<
            template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
            BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)
        >
        struct rewrite_object<T<BOOST_PP_ENUM_PARAMS(N, A)> BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(N)>
        {
            typedef
                T<BOOST_PP_ENUM_BINARY_PARAMS(N, typename rewrite_object<A, >::type BOOST_PP_INTERCEPT)>
            type;
        };

        #define M0(Z, N, DATA)                                                                      \
            BOOST_PP_CAT(Local, N)(BOOST_PP_CAT(Init, N))                                           \
            /**/

        #define M1(Z, N, DATA)                                                                      \
            typedef                                                                                 \
                typename when<_, BOOST_PP_CAT(Init, N)>::template impl<Expr, State, Data>           \
            BOOST_PP_CAT(fun_type, N);                                                              \
            typedef                                                                                 \
                fusion::pair<                                                                       \
                    BOOST_PP_CAT(Local, N)                                                          \
                  , typename BOOST_PP_CAT(fun_type, N)::result_type                                 \
                >                                                                                   \
            BOOST_PP_CAT(value_type, N);                                                            \
            /**/

        #define M2(Z, N, DATA)                                                                      \
            BOOST_PP_CAT(value_type, N)(BOOST_PP_CAT(fun_type, N)()(e, s, d))                       \
            /**/

        template<typename Expr, typename State, typename Data
            BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Local)
            BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Init)
          , typename Transform
        >
        struct init_local_map<Expr, State, Data
            BOOST_PP_ENUM_TRAILING(N, M0, ~)
          , Transform
        > : transform_impl<Expr, State, Data>
        {
            // Rewrite the transform to make our monkeying with the data parameter
            // transparent and to properly scope the local variables.
            typedef typename detail::rewrite_transform<Transform>::type transform_type;
            BOOST_PP_REPEAT(N, M1, ~)
            typedef fusion::map<BOOST_PP_ENUM_PARAMS(N, value_type)> local_map_type;

            static local_map_type call(
                typename init_local_map::expr_param e
              , typename init_local_map::state_param s
              , typename init_local_map::data_param d
            )
            {
                return local_map_type(BOOST_PP_ENUM(N, M2, ~));
            }
        };

        #undef M2
        #undef M1
        #undef M0

        #endif

        // rewrite_makeable
        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct rewrite_makeable<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef
                proto::make<typename rewrite_object<R>::type(BOOST_PP_ENUM_PARAMS(N, A))>
            type;
        };

        template<typename Object BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct rewrite_makeable<Object(*)(BOOST_PP_ENUM_PARAMS(N, A))>
          : rewrite_makeable<Object(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

        // rewrite_lazyable
        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
        struct rewrite_lazyable<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef
                proto::lazy<typename rewrite_object<R>::type(BOOST_PP_ENUM_PARAMS(N, A))>
            type;
        };

        // rewrite_lazyable
        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
        struct rewrite_lazyable<R(*)(BOOST_PP_ENUM_PARAMS(N, A))>
          : rewrite_lazyable<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

        // rewrite_transform
        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
        struct rewrite_transform<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef typename rewrite_args<R(BOOST_PP_ENUM_PARAMS(N, A))>::type fun_type;
            typedef
                typename mpl::eval_if_c<
                    is_callable<R>::value
                  , rewrite_callable<fun_type>
                  , rewrite_makeable<fun_type>
                >::type
            type;
        };

        template<typename R BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A) >
        struct rewrite_transform<R(*)(BOOST_PP_ENUM_PARAMS(N, A))>
          : rewrite_transform<R(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

    #undef N

#endif
