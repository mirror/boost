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

    template<typename OpTag, typename Node, typename State = fusion::nil>
    struct expand_left_view
      : compile_result<Node, State, mpl::void_, expand_left_tag<OpTag> >
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

    template<typename Cons>
    struct binary_tree_iterator
      : fusion::iterator_base<binary_tree_iterator<Cons> >
      , Cons
    {
        typedef binary_tree_iterator_tag tag;
        typedef mpl::forward_iterator_tag category;

        explicit binary_tree_iterator(Cons const &cons)
          : Cons(cons)
        {}
    };

    namespace binary_tree_detail
    {
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

        template<typename Sequence>
        struct begin_impl
        {
            typedef typename tag_type<Sequence>::type tag_type;
            typedef binary_tree_iterator<typename expand_left_view<tag_type, Sequence>::type> type;

            static type call(Sequence const &node)
            {
                return type(expand_left<tag_type>(node));
            }
        };

        struct end_impl
        {
            typedef binary_tree_iterator<fusion::nil> type;

            template<typename Sequence>
            static type call(Sequence const &)
            {
                return type(fusion::nil());
            }
        };

        template<typename Iterator>
        struct value_impl
          : remove_cv<typename remove_reference<typename Iterator::car_type>::type>
        {};

        // discards the old head, expands the right child of the new head
        // and pushes the result to the head of the list.
        template<typename Iterator, typename Parents = typename Iterator::cdr_type>
        struct next_impl
        {
            typedef typename value_impl<Parents>::type node_type;
            typedef typename tag_type<node_type>::type tag_type;
            typedef typename right_type<node_type>::type right_type;
            typedef binary_tree_iterator<
                typename expand_left_view<tag_type, right_type, typename Parents::cdr_type>::type
            > type;

            static type call(Iterator const &it)
            {
                return type(expand_left<tag_type>(proto::right(it.cdr.car), it.cdr.cdr));
            }
        };

        template<typename Iterator>
        struct next_impl<Iterator, fusion::nil> // no more parents, end of tree traversal
          : end_impl
        {};

        template<typename Iterator>
        struct deref_impl
        {
            typedef typename Iterator::car_type type;

            static type call(Iterator const &it)
            {
                return it.car;
            }
        };
    } // namespace binary_tree_detail

    template<typename OpTag>
    struct compiler<OpTag, expand_left_tag<OpTag> >
      : binary_tree_detail::expand_left_compiler<expand_left_tag<OpTag> >
    {};

    template<typename OpTag, typename OtherOpTag>
    struct compiler<OtherOpTag, expand_left_tag<OpTag> >
      : binary_tree_detail::cons_ref_compiler
    {};

}}

namespace boost { namespace fusion { namespace meta
{
    template<typename OpTag>
    struct begin_impl<proto::tag<OpTag> >
    {
        template<typename Sequence>
        struct apply
          : proto::binary_tree_detail::begin_impl<Sequence>
        {};
    };

    template<typename OpTag>
    struct end_impl<proto::tag<OpTag> >
    {
        template<typename Sequence>
        struct apply
          : proto::binary_tree_detail::end_impl
        {};
    };

    template<>
    struct value_impl<proto::binary_tree_iterator_tag>
    {
        template<typename Iterator>
        struct apply
          : proto::binary_tree_detail::value_impl<Iterator>
        {};
    };

    template<>
    struct next_impl<proto::binary_tree_iterator_tag>
    {
        template<typename Iterator>
        struct apply
          : proto::binary_tree_detail::next_impl<Iterator>
        {};
    };

    template<>
    struct deref_impl<proto::binary_tree_iterator_tag>
    {
        template<typename Iterator>
        struct apply
          : proto::binary_tree_detail::deref_impl<Iterator>
        {};
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

    template<typename Cons>
    struct next<proto::binary_tree_iterator<Cons> >
      : proto::binary_tree_detail::next_impl<proto::binary_tree_iterator<Cons> >
    {
    };

    template<typename Cons>
    struct deref<proto::binary_tree_iterator<Cons> >
      : proto::binary_tree_detail::value_impl<proto::binary_tree_iterator<Cons> >
    {
    };

}} // namespace boost::mpl

#endif
