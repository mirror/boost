    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_.hpp
    /// Contains definition of make_expr_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<
        typename Tag
      , typename Domain
        , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void
      , typename _ = void
    >
    struct make_expr_
    {};
    template<typename Domain, typename A>
    struct make_expr_<tag::terminal, Domain, A
        , void , void , void , void , void>
    {
        typedef typename proto::detail::protoify<A, Domain>::result_type result_type;
        result_type operator()(typename add_reference<A>::type a) const
        {
            return proto::detail::protoify<A, Domain>()(a);
        }
    };
    template<typename A>
    struct make_expr_<tag::terminal, deduce_domain, A
        , void , void , void , void , void>
      : make_expr_<tag::terminal, default_domain, A>
    {};
    template<typename Tag, typename Domain , typename A0>
    struct make_expr_<Tag, Domain , A0
        , void , void , void , void, void>
    {
        typedef
            list1<
                typename boost::proto::detail::protoify< A0 , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        result_type operator()(typename add_reference<A0 >::type a0) const
        {
            expr_type const that = {
                boost::proto::detail::protoify< A0 , Domain >()(a0)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag , typename A0>
    struct make_expr_<Tag, deduce_domain , A0
        , void , void , void , void, void>
      : make_expr_<
            Tag
          , typename deduce_domain1<A0>::type
            , A0
        >
    {};
    template<typename Tag, typename Domain , typename A0 , typename A1>
    struct make_expr_<Tag, Domain , A0 , A1
        , void , void , void, void>
    {
        typedef
            list2<
                typename boost::proto::detail::protoify< A0 , Domain >::result_type , typename boost::proto::detail::protoify< A1 , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        result_type operator()(typename add_reference<A0 >::type a0 , typename add_reference<A1 >::type a1) const
        {
            expr_type const that = {
                boost::proto::detail::protoify< A0 , Domain >()(a0) , boost::proto::detail::protoify< A1 , Domain >()(a1)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag , typename A0 , typename A1>
    struct make_expr_<Tag, deduce_domain , A0 , A1
        , void , void , void, void>
      : make_expr_<
            Tag
          , typename deduce_domain2<A0 , A1>::type
            , A0 , A1
        >
    {};
    template<typename Tag, typename Domain , typename A0 , typename A1 , typename A2>
    struct make_expr_<Tag, Domain , A0 , A1 , A2
        , void , void, void>
    {
        typedef
            list3<
                typename boost::proto::detail::protoify< A0 , Domain >::result_type , typename boost::proto::detail::protoify< A1 , Domain >::result_type , typename boost::proto::detail::protoify< A2 , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        result_type operator()(typename add_reference<A0 >::type a0 , typename add_reference<A1 >::type a1 , typename add_reference<A2 >::type a2) const
        {
            expr_type const that = {
                boost::proto::detail::protoify< A0 , Domain >()(a0) , boost::proto::detail::protoify< A1 , Domain >()(a1) , boost::proto::detail::protoify< A2 , Domain >()(a2)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag , typename A0 , typename A1 , typename A2>
    struct make_expr_<Tag, deduce_domain , A0 , A1 , A2
        , void , void, void>
      : make_expr_<
            Tag
          , typename deduce_domain3<A0 , A1 , A2>::type
            , A0 , A1 , A2
        >
    {};
    template<typename Tag, typename Domain , typename A0 , typename A1 , typename A2 , typename A3>
    struct make_expr_<Tag, Domain , A0 , A1 , A2 , A3
        , void, void>
    {
        typedef
            list4<
                typename boost::proto::detail::protoify< A0 , Domain >::result_type , typename boost::proto::detail::protoify< A1 , Domain >::result_type , typename boost::proto::detail::protoify< A2 , Domain >::result_type , typename boost::proto::detail::protoify< A3 , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        result_type operator()(typename add_reference<A0 >::type a0 , typename add_reference<A1 >::type a1 , typename add_reference<A2 >::type a2 , typename add_reference<A3 >::type a3) const
        {
            expr_type const that = {
                boost::proto::detail::protoify< A0 , Domain >()(a0) , boost::proto::detail::protoify< A1 , Domain >()(a1) , boost::proto::detail::protoify< A2 , Domain >()(a2) , boost::proto::detail::protoify< A3 , Domain >()(a3)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3>
    struct make_expr_<Tag, deduce_domain , A0 , A1 , A2 , A3
        , void, void>
      : make_expr_<
            Tag
          , typename deduce_domain4<A0 , A1 , A2 , A3>::type
            , A0 , A1 , A2 , A3
        >
    {};
    template<typename Tag, typename Domain , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make_expr_<Tag, Domain , A0 , A1 , A2 , A3 , A4
        , void>
    {
        typedef
            list5<
                typename boost::proto::detail::protoify< A0 , Domain >::result_type , typename boost::proto::detail::protoify< A1 , Domain >::result_type , typename boost::proto::detail::protoify< A2 , Domain >::result_type , typename boost::proto::detail::protoify< A3 , Domain >::result_type , typename boost::proto::detail::protoify< A4 , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type result_type;
        result_type operator()(typename add_reference<A0 >::type a0 , typename add_reference<A1 >::type a1 , typename add_reference<A2 >::type a2 , typename add_reference<A3 >::type a3 , typename add_reference<A4 >::type a4) const
        {
            expr_type const that = {
                boost::proto::detail::protoify< A0 , Domain >()(a0) , boost::proto::detail::protoify< A1 , Domain >()(a1) , boost::proto::detail::protoify< A2 , Domain >()(a2) , boost::proto::detail::protoify< A3 , Domain >()(a3) , boost::proto::detail::protoify< A4 , Domain >()(a4)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make_expr_<Tag, deduce_domain , A0 , A1 , A2 , A3 , A4
        , void>
      : make_expr_<
            Tag
          , typename deduce_domain5<A0 , A1 , A2 , A3 , A4>::type
            , A0 , A1 , A2 , A3 , A4
        >
    {};
