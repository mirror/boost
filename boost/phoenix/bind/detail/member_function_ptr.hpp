/*=============================================================================
Copyright (c) 2001-2007 Joel de Guzman

Distributed under the Boost Software License, Version 1.0. (See accompanying 
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_BIND_DETAIL_MEMBER_FUNCTION_PTR_HPP
#define BOOST_PHOENIX_BIND_DETAIL_MEMBER_FUNCTION_PTR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/support/iterate.hpp>

namespace boost { namespace phoenix { namespace detail
{
    template <int N>
    struct member_function_ptr_impl
    {
        template <typename RT, typename FP>
        struct impl;
    };

    template <int N, typename RT, typename FP>
    struct member_function_ptr
        : member_function_ptr_impl<N>::template impl<RT, FP>
    {
        typedef typename member_function_ptr_impl<N>::
            template impl<RT, FP> base;
        member_function_ptr(FP fp)
            : base(fp) {}
        
        using base::fp;

        bool operator==(member_function_ptr const & rhs) const
        {
            return fp == rhs.fp;
        }

        template <int M, typename RhsRT, typename RhsFP>
        bool operator==(member_function_ptr<M, RhsRT, RhsFP> const & rhs) const
        {
            return false;
        }
    };

    BOOST_PROTO_USE_GET_POINTER();

    template <>
    struct member_function_ptr_impl<0>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp)
                : fp(fp) {}

            template <typename Class>
            RT operator()(Class& obj) const
            {
                typedef typename proto::detail::classtypeof<FP>::type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj) ->*fp)();
            }

            template <typename Class>
            RT operator()(Class* obj) const
            {
                return (obj->*fp)();
            }

            FP fp;
        };
    };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/bind/detail/member_function_ptr.hpp>))
#include BOOST_PHOENIX_ITERATE()

}}} // namespace boost::phoenix::detail

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else

    template <>
    struct member_function_ptr_impl<BOOST_PHOENIX_ITERATION>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;

            impl(FP fp)
                : fp(fp) {}

            template <typename Class, BOOST_PHOENIX_typename_A>
            RT operator()(Class& obj, BOOST_PHOENIX_A_const_ref_a) const
            {
                typedef typename proto::detail::classtypeof<FP>::type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(BOOST_PHOENIX_a);
            }

            template <typename Class, BOOST_PHOENIX_typename_A>
            RT operator()(Class* obj, BOOST_PHOENIX_A_const_ref_a) const
            {
                return (obj->*fp)(BOOST_PHOENIX_a);
            }

            FP fp;
        };
    };

#endif // defined(BOOST_PP_IS_ITERATING)
