///////////////////////////////////////////////////////////////////////////////
/// \file arg_traits.hpp
/// Contains definitions for value_type\<\>, arg_type\<\>, left_type\<\>,
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

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // value_type
    //  specialize this to control how user-defined types are stored in the parse tree
    template<typename T>
    struct value_type
    {
        typedef typename boost::call_traits<T>::value_type type;
    };

    template<>
    struct value_type<fusion::void_t>
    {
        typedef fusion::void_t type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct arg_type
    {
        typedef typename Node::arg_type type;
        typedef type const &const_reference;
    };

    template<typename Node, typename Param>
    struct arg_type<op_proxy<Node, Param> >
    {
        typedef typename Node::arg_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct left_type
    {
        typedef typename Node::left_type type;
        typedef type const &const_reference;
    };

    template<typename Node, typename Param>
    struct left_type<op_proxy<Node, Param> >
    {
        typedef typename Node::left_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename Node>
    struct right_type
    {
        typedef typename Node::right_type type;
        typedef type const &const_reference;
    };

    template<typename Node, typename Param>
    struct right_type<op_proxy<Node, Param> >
    {
        typedef typename Node::right_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // tag extractor
    template<typename Node>
    struct tag_type
    {
        typedef typename Node::tag_type type;
    };

    template<typename Node, typename Param>
    struct tag_type<op_proxy<Node, Param> >
    {
        typedef typename Node::tag_type type;
    };

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
    inline typename arg_type<Node>::const_reference arg(Node const &node)
    {
        return node.cast().arg;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // left
    template<typename Node>
    inline typename left_type<Node>::const_reference left(Node const &node)
    {
        return node.cast().left;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // right
    template<typename Node>
    inline typename right_type<Node>::const_reference right(Node const &node)
    {
        return node.cast().right;
    }

}}

#endif
