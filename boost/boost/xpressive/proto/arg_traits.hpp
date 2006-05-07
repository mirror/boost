///////////////////////////////////////////////////////////////////////////////
/// \file arg_traits.hpp
/// Contains definitions for arg_type\<\>, left_type\<\>,
/// right_type\<\>, tag_type\<\>, and the helper functions arg(), left(),
/// and right().
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

#include <boost/call_traits.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/op_tags.hpp>

#ifdef BOOST_PROTO_FUSION_V2
# include <boost/fusion/sequence/intrinsic/at.hpp>
# define BOOST_PROTO_AT(n, s) fusion::at_c<n>(s)
#else
# include <boost/spirit/fusion/sequence/at.hpp>
# define BOOST_PROTO_AT(n, s) fusion::at<n>(s)
#endif

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct arg_type
    {
        typedef typename remove_reference<typename Node::arg_type>::type type;
        typedef typename add_reference<typename add_const<type>::type>::type reference;
    };

    template<typename Node, typename Param>
    struct arg_type<op_proxy<Node, Param> >
    {
        typedef typename remove_reference<typename Node::arg_type>::type type;
        typedef typename add_const<type>::type reference;
    };

    template<typename Node>
    struct arg_type<Node &>
      : arg_type<Node>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct left_type
    {
        typedef typename remove_reference<typename Node::left_type>::type type;
        typedef typename add_reference<typename add_const<type>::type>::type reference;
    };

    template<typename Node, typename Param>
    struct left_type<op_proxy<Node, Param> >
    {
        typedef typename remove_reference<typename Node::left_type>::type type;
        typedef typename add_const<type>::type reference;
    };

    template<typename Node>
    struct left_type<Node &>
      : left_type<Node>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct right_type
    {
        typedef typename remove_reference<typename Node::right_type>::type type;
        typedef typename add_reference<typename add_const<type>::type>::type reference;
    };

    template<typename Node, typename Param>
    struct right_type<op_proxy<Node, Param> >
    {
        typedef typename remove_reference<typename Node::right_type>::type type;
        typedef typename add_const<type>::type reference;
    };

    template<typename Node>
    struct right_type<Node &>
      : right_type<Node>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // tag extractor
    template<typename Node, bool IsOp>
    struct tag_type
    {
        typedef typename Node::tag_type type;
    };

    template<typename Node, typename Param>
    struct tag_type<op_proxy<Node, Param>, true>
    {
        typedef typename Node::tag_type type;
    };

    template<typename Node>
    struct tag_type<Node, false>
    {
        typedef noop_tag type;
    };

    template<typename Node>
    struct tag_type<Node &, true>
      : tag_type<Node, true>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_unary
    template<typename Node>
    struct is_unary
      : boost::is_base_and_derived<unary_tag, typename tag_type<Node>::type>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_binary
    template<typename Node>
    struct is_binary
      : boost::is_base_and_derived<binary_tag, typename tag_type<Node>::type>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // is_nary
    template<typename Node>
    struct is_nary
      : boost::is_base_and_derived<nary_tag, typename tag_type<Node>::type>
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // arg
    template<typename Node>
    inline typename arg_type<Node>::reference arg(Node const &node)
    {
        return node.cast().child.val;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // left
    template<typename Node>
    inline typename left_type<Node>::reference left(Node const &node)
    {
        return BOOST_PROTO_AT(0, node.cast().children).val;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // right
    template<typename Node>
    inline typename right_type<Node>::reference right(Node const &node)
    {
        return BOOST_PROTO_AT(1, node.cast().children).val;
    }

}}

#endif
