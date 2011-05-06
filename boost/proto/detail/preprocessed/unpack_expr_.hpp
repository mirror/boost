    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_.hpp
    /// Contains definition of make_expr_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Tag, typename Domain, typename Sequence, std::size_t Size>
    struct unpack_expr_
    {};
    template<typename Domain, typename Sequence>
    struct unpack_expr_<tag::terminal, Domain, Sequence, 1u>
    {
        typedef
            typename add_const<
                typename fusion::result_of::value_of<
                    typename fusion::result_of::begin<Sequence>::type
                >::type
            >::type
        terminal_type;
        typedef
            typename proto::detail::protoify<
                terminal_type
              , Domain
            >::result_type
        type;
        static type const call(Sequence const &sequence)
        {
            return proto::detail::protoify<terminal_type, Domain>()(fusion::at_c<0>(sequence));
        }
    };
    template<typename Sequence>
    struct unpack_expr_<tag::terminal, deduce_domain, Sequence, 1u>
      : unpack_expr_<tag::terminal, default_domain, Sequence, 1u>
    {};
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 1>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0;
        typedef
            list1<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 1>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain1<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type
                >::type
              , Sequence
              , 1
            >
        other;
        typedef typename other::type type;
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 2>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1;
        typedef
            list2<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 2>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain2<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type
                >::type
              , Sequence
              , 2
            >
        other;
        typedef typename other::type type;
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 3>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2;
        typedef
            list3<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 3>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain3<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type
                >::type
              , Sequence
              , 3
            >
        other;
        typedef typename other::type type;
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 4>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3;
        typedef
            list4<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 4>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain4<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type
                >::type
              , Sequence
              , 4
            >
        other;
        typedef typename other::type type;
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 5>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4;
        typedef
            list5<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 5>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain5<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type
                >::type
              , Sequence
              , 5
            >
        other;
        typedef typename other::type type;
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
