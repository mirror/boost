///////////////////////////////////////////////////////////////////////////////
// arg_traits.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

#include <boost/call_traits.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

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
    template<typename OpT>
    struct arg_type
    {
        typedef typename OpT::arg_type type;
        typedef type const &const_reference;
    };

    template<typename OpT, typename ParamT>
    struct arg_type<op_proxy<OpT, ParamT> >
    {
        typedef typename OpT::arg_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename OpT>
    struct left_type
    {
        typedef typename OpT::left_type type;
        typedef type const &const_reference;
    };

    template<typename OpT, typename ParamT>
    struct left_type<op_proxy<OpT, ParamT> >
    {
        typedef typename OpT::left_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // argument type extractors
    template<typename OpT>
    struct right_type
    {
        typedef typename OpT::right_type type;
        typedef type const &const_reference;
    };

    template<typename OpT, typename ParamT>
    struct right_type<op_proxy<OpT, ParamT> >
    {
        typedef typename OpT::right_type type;
        typedef type const const_reference;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // tag extractor
    template<typename OpT>
    struct tag_type
    {
        typedef typename OpT::tag_type type;
    };

    template<typename OpT, typename ParamT>
    struct tag_type<op_proxy<OpT, ParamT> >
    {
        typedef typename OpT::tag_type type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // arg
    template<typename OpT>
    inline typename arg_type<OpT>::const_reference arg(OpT const &op)
    {
        return op.cast().arg;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // left
    template<typename OpT>
    inline typename left_type<OpT>::const_reference left(OpT const &op)
    {
        return op.cast().left;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // right
    template<typename OpT>
    inline typename right_type<OpT>::const_reference right(OpT const &op)
    {
        return op.cast().right;
    }

}}

#endif
