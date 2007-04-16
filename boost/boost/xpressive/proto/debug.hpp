///////////////////////////////////////////////////////////////////////////////
/// \file debug.hpp
/// Utilities for debugging proto expression trees
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006
#define BOOST_PROTO_DEBUG_HPP_EAN_12_31_2006

#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#if !defined(__WAVE__) || !defined(BOOST_PROTO_DOXYGEN_INVOKED)
#include <iomanip>
#include <iostream>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/xpressive/proto/traits.hpp>
#else
/// INTERNAL ONLY
/// Needed to work around doxygen bug
struct a_dummy_global;
#endif

namespace boost { namespace proto
{
    namespace tag
    {
        template<typename Tag>
        inline char const *proto_tag_name(Tag)
        {
            return typeid(Tag).name();
        }

    #define BOOST_PROTO_DEFINE_TAG_NAME(Tag)\
        inline char const *proto_tag_name(tag::Tag)\
        {\
            return #Tag;\
        }\
        /**/

        BOOST_PROTO_DEFINE_TAG_NAME(unary_plus)
        BOOST_PROTO_DEFINE_TAG_NAME(unary_minus)
        BOOST_PROTO_DEFINE_TAG_NAME(unary_star)
        BOOST_PROTO_DEFINE_TAG_NAME(complement)
        BOOST_PROTO_DEFINE_TAG_NAME(address_of)
        BOOST_PROTO_DEFINE_TAG_NAME(logical_not)
        BOOST_PROTO_DEFINE_TAG_NAME(pre_inc)
        BOOST_PROTO_DEFINE_TAG_NAME(pre_dec)
        BOOST_PROTO_DEFINE_TAG_NAME(post_inc)
        BOOST_PROTO_DEFINE_TAG_NAME(post_dec)
        BOOST_PROTO_DEFINE_TAG_NAME(left_shift)
        BOOST_PROTO_DEFINE_TAG_NAME(right_shift)
        BOOST_PROTO_DEFINE_TAG_NAME(multiply)
        BOOST_PROTO_DEFINE_TAG_NAME(divide)
        BOOST_PROTO_DEFINE_TAG_NAME(modulus)
        BOOST_PROTO_DEFINE_TAG_NAME(add)
        BOOST_PROTO_DEFINE_TAG_NAME(subtract)
        BOOST_PROTO_DEFINE_TAG_NAME(less)
        BOOST_PROTO_DEFINE_TAG_NAME(greater)
        BOOST_PROTO_DEFINE_TAG_NAME(less_equal)
        BOOST_PROTO_DEFINE_TAG_NAME(greater_equal)
        BOOST_PROTO_DEFINE_TAG_NAME(equal)
        BOOST_PROTO_DEFINE_TAG_NAME(not_equal)
        BOOST_PROTO_DEFINE_TAG_NAME(logical_or)
        BOOST_PROTO_DEFINE_TAG_NAME(logical_and)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_and)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_or)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_xor)
        BOOST_PROTO_DEFINE_TAG_NAME(comma)
        BOOST_PROTO_DEFINE_TAG_NAME(mem_ptr)
        BOOST_PROTO_DEFINE_TAG_NAME(assign)
        BOOST_PROTO_DEFINE_TAG_NAME(left_shift_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(right_shift_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(multiply_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(divide_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(modulus_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(add_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(subtract_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_and_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_or_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(bitwise_xor_assign)
        BOOST_PROTO_DEFINE_TAG_NAME(subscript)
        BOOST_PROTO_DEFINE_TAG_NAME(function)

    #undef BOOST_PROTO_DEFINE_TAG_NAME
    }

    namespace op
    {
        // Display a proto expression tree
        struct display_expr
        {
            display_expr(int depth = 0, std::ostream &sout = std::cout)
              : depth_(depth)
              , first_(true)
              , sout_(sout)
            {}

            template<typename Args>
            void operator()(expr<tag::terminal, Args, 1> const &expr) const
            {
                this->sout_ << std::setw(this->depth_) << (this->first_? "" : ", ")
                    << "terminal(" << proto::arg(expr) << ")\n";
                this->first_ = false;
            }

        #define BOOST_PROTO_ARG(z, n, data)\
            display(proto::arg_c<n>(expr));\
            /**/

        #define BOOST_PP_LOCAL_MACRO(N)\
            template<typename Tag, typename Args>\
            void operator()(expr<Tag, Args, N> const &expr) const\
            {\
                this->sout_ << std::setw(this->depth_) << (this->first_? "" : ", ")\
                    << proto_tag_name(Tag()) << "(\n";\
                display_expr display(this->depth_ + 4, this->sout_);\
                BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_ARG, _)\
                this->sout_ << std::setw(this->depth_) << "" << ")\n";\
                this->first_ = false;\
            }\
            /**/

        #define BOOST_PP_LOCAL_LIMITS (1, BOOST_PROTO_MAX_ARITY)
        #include BOOST_PP_LOCAL_ITERATE()
        #undef BOOST_PROTO_ARG

            template<typename T>
            void operator()(T const &t) const
            {
                (*this)(t.cast());
            }

        private:
            int depth_;
            mutable bool first_;
            std::ostream &sout_;
        };
    }

    template<typename Expr>
    void display_expr(Expr const &expr)
    {
        op::display_expr()(expr);
    }

    template<typename Expr>
    void display_expr(Expr const &expr, std::ostream &sout)
    {
        op::display_expr(0, sout)(expr);
    }

}}

#endif
