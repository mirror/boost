///////////////////////////////////////////////////////////////////////////////
/// \file fusion.hpp
/// Make a binary proto parse tree a valid Fusion sequence
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUSION_HPP_EAN_04_29_2006
#define BOOST_PROTO_FUSION_HPP_EAN_04_29_2006

#include <boost/xpressive/proto/proto.hpp>
#include <boost/spirit/fusion/sequence/cons.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost { namespace proto
{
    template<typename OpTag>
    struct expand_left_tag
    {};

    template<typename DomainTag>
    struct expand_left_compiler
    {
        template<typename Node, typename State, typename Visitor>
        struct apply
          : compile_result<
                typename left_type<Node>::type
              , fusion::cons<Node const &, State>
              , Visitor
              , DomainTag
            >
        {};

        template<typename Node, typename State, typename Visitor>
        static typename apply<Node, State, Visitor>::type
        call(Node const &node, State const &state, Visitor &visitor)
        {
            return proto::compile(
                proto::left(node)
              , fusion::cons<Node const &, State>(node, state)
              , visitor
              , DomainTag()
            );
        }
    };

    struct cons_ref_compiler
    {
        template<typename Node, typename State, typename Visitor>
        struct apply
        {
            typedef fusion::cons<Node const &, State> type;
        };

        template<typename Node, typename State, typename Visitor>
        static fusion::cons<Node const &, State>
        call(Node const &node, State const &state, Visitor &)
        {
            return fusion::cons<Node const &, State>(node, state);
        }
    };

    template<typename OpTag>
    struct compiler<OpTag, expand_left_tag<OpTag> >
      : expand_left_compiler<expand_left_tag<OpTag> >
    {};

    template<typename OpTag, typename OtherOpTag>
    struct compiler<OtherOpTag, expand_left_tag<OpTag> >
      : cons_ref_compiler
    {};

    template<typename OpTag, typename Node, typename State = fusion::nil>
    struct expand_left_view
      : compile_result<
            Node
          , State
          , mpl::void_
          , expand_left_tag<OpTag>
        >
    {};

    template<typename OpTag, typename Node, typename State>
    typename expand_left_view<OpTag, Node, State>::type
    expand_left(Node const &node, State const &state)
    {
        mpl::void_ null;
        return compile(node, state, null, expand_left_tag<OpTag>());
    }

    template<typename OpTag, typename Node>
    typename expand_left_view<OpTag, Node>::type
    expand_left(Node const &node)
    {
        return expand_left<OpTag>(node, fusion::nil());
    }

    struct binary_tree_iterator_tag;

    template<typename Parents>
    struct binary_tree_iterator
      : fusion::iterator_base<binary_tree_iterator<Parents> >
    {
        typedef Parents parents_type;
        typedef binary_tree_iterator_tag tag;
        typedef mpl::forward_iterator_tag category;

        explicit binary_tree_iterator(Parents const &parents_)
          : parents(parents_)
        {}

        Parents parents;
    };

}}

namespace boost { namespace fusion { namespace meta
{
    template<typename T>
    struct remove_cv_ref
      : remove_cv<typename remove_reference<T>::type>
    {};

    template<>
    struct value_impl<proto::binary_tree_iterator_tag>
    {
        template<typename Iterator>
        struct apply
          : remove_cv_ref<typename Iterator::parents_type::car_type>
        {};
    };

    template<>
    struct deref_impl<proto::binary_tree_iterator_tag>
    {
        template<typename Iterator>
        struct apply
        {
            typedef typename Iterator::parents_type::car_type type;

            static type call(Iterator const &it)
            {
                return it.parents.car;
            }
        };
    };

    template<>
    struct next_impl<proto::binary_tree_iterator_tag>
    {
        // discards the old head, expands the right child of the new head
        // and pushes the result to the head of the list.
        template<typename Iterator>
        struct apply
        {
            typedef typename Iterator::parents_type::cdr_type parents_type;
            typedef typename remove_cv_ref<typename parents_type::car_type>::type node_type;
            typedef typename proto::tag_type<node_type>::type op_tag;
            typedef typename proto::right_type<node_type>::type right_type;
            typedef typename proto::expand_left_view<
                op_tag
              , right_type
              , typename parents_type::cdr_type
            >::type new_parents_type;
            typedef proto::binary_tree_iterator<new_parents_type> type;

            static type call(Iterator const &it)
            {
                return type(proto::expand_left<op_tag>(
                    proto::right(it.parents.cdr.car)
                  , it.parents.cdr.cdr
                ));
            }
        };

        template<typename Car>
        struct apply<proto::binary_tree_iterator<cons<Car, nil> > >
        {
            typedef proto::binary_tree_iterator<nil> type;

            static type call(proto::binary_tree_iterator<cons<Car, nil> > const &)
            {
                return type(nil());
            }
        };
    };

    template<typename OpTag>
    struct begin_impl<proto::tag<OpTag> >
    {
        template<typename Sequence>
        struct apply
        {
            typedef typename proto::expand_left_view<OpTag, Sequence>::type parents_type;
            typedef proto::binary_tree_iterator<parents_type> type;

            static type call(Sequence const &node)
            {
                return type(proto::expand_left<OpTag>(node));
            }
        };
    };

    template<typename OpTag>
    struct end_impl<proto::tag<OpTag> >
    {
        template<typename Sequence>
        struct apply
        {
            typedef proto::binary_tree_iterator<nil> type;

            static type call(Sequence const &)
            {
                return type(nil());
            }
        };
    };

}}}

namespace boost { namespace mpl
{
    template<typename OpTag>
    struct begin_impl<proto::tag<OpTag> >
      : fusion::meta::begin_impl<proto::tag<OpTag> >
    {
    };

    template<typename OpTag>
    struct end_impl<proto::tag<OpTag> >
      : fusion::meta::end_impl<proto::tag<OpTag> >
    {
    };

    template<typename Parents>
    struct next<proto::binary_tree_iterator<Parents> >
      : fusion::meta::next_impl<proto::binary_tree_iterator_tag>
            ::apply<proto::binary_tree_iterator<Parents> >
    {
    };

    template<typename Parents>
    struct deref<proto::binary_tree_iterator<Parents> >
      : fusion::meta::value_impl<proto::binary_tree_iterator_tag>
            ::apply<proto::binary_tree_iterator<Parents> >
    {
    };

}} // namespace boost::mpl

#endif
