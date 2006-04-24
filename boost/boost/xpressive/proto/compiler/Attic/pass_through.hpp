///////////////////////////////////////////////////////////////////////////////
/// \file pass_through.hpp
/// 
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006
#define BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{
    ///////////////////////////////////////////////////////////////////////////////
    // pass_through_compiler
    template<typename DomainTag>
    struct pass_through_compiler
    {
        // compile_helper
        template<typename Node, typename State, typename Visitor, typename EnableIf = void>
        struct compile_helper
        {
            typedef typename compile_result<Node, State, Visitor, DomainTag>::type type;

            static type const &call(type const &node, State const &state, Visitor &visitor, int)
            {
                return node;
            }

            static type const call(Node const &node, State const &state, Visitor &visitor, ...)
            {
                return proto::compile(node, state, visitor, DomainTag());
            }
        };

        template<typename Node, typename State, typename Visitor>
        struct compile_helper<Node, State, Visitor, typename disable_if<is_op<Node> >::type>
        {
            typedef Node type;

            static Node const &call(Node const &node, State const &state, Visitor &visitor, int)
            {
                return node;
            }
        };

        // apply_helper
        template<typename Node, typename State, typename Visitor, typename EnableIf>
        struct apply_helper;

        // is_unary apply
        template<typename Node, typename State, typename Visitor>
        struct apply_helper<Node, State, Visitor, typename enable_if<is_unary<Node> >::type>
        {
            typedef typename arg_type<Node>::type arg_type;
            typedef compile_helper<arg_type, State, Visitor> compiler_type;
            typedef typename compiler_type::type new_arg_type;
            typedef unary_op<new_arg_type, typename tag_type<Node>::type> type;
            typedef typename mpl::if_<is_same<Node, type>, Node const &, type const>::type const_reference;

            static type const &call(type const &node, State const &state, Visitor &visitor, int)
            {
                return node; // pass-through, no recompilation necessary.
            }

            static type const call(Node const &node, State const &state, Visitor &visitor, ...)
            {
                return proto::make_op<typename tag_type<Node>::type>(
                    compiler_type::call(proto::arg(node), state, visitor, 0)
                );
            }
        };

        // is_binary apply
        template<typename Node, typename State, typename Visitor>
        struct apply_helper<Node, State, Visitor, typename enable_if<is_binary<Node> >::type>
        {
            typedef typename left_type<Node>::type left_type;
            typedef typename right_type<Node>::type right_type;
            typedef compile_helper<left_type, State, Visitor> left_compiler_type;
            typedef compile_helper<right_type, State, Visitor> right_compiler_type;
            typedef typename left_compiler_type::type new_left_type;
            typedef typename right_compiler_type::type new_right_type;
            typedef binary_op<new_left_type, new_right_type, typename tag_type<Node>::type> type;
            typedef typename mpl::if_<is_same<Node, type>, Node const &, type const>::type const_reference;

            static type const &call(type const &node, State const &state, Visitor &visitor, int)
            {
                return node; // pass-through, no recompilation necessary.
            }

            static type const call(Node const &node, State const &state, Visitor &visitor, ...)
            {
                return proto::make_op<typename tag_type<Node>::type>(
                    left_compiler_type::call(proto::left(node), state, visitor, 0)
                  , right_compiler_type::call(proto::right(node), state, visitor, 0)
                );
            }
        };

        // is_nary apply
        template<typename Node, typename State, typename Visitor>
        struct apply_helper<Node, State, Visitor, typename enable_if<is_nary<Node> >::type>
        {
            // BUGBUG handle nary_op here
            typedef Node type;
            typedef Node const &const_reference;

            static Node const &call(Node const &node, State const &, Visitor &)
            {
                return node;
            }
        };

        template<typename Node, typename State, typename Visitor>
        struct apply
          : apply_helper<Node, State, Visitor, void>
        {
        };

        template<typename Node, typename State, typename Visitor>
        static typename apply<Node, State, Visitor>::const_reference
        call(Node const &node, State const &state, Visitor &visitor)
        {
            return apply<Node, State, Visitor>::call(node, state, visitor, 0);
        }
    };

}}

#endif
